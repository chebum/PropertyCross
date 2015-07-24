#include "position.h"
#include <QGeoCoordinate>
#include <QDebug>
#include <QString>

Position::Position(QObject* parent) :
    QObject(parent)
{

}

void Position::getPosition()
{
   m_positionSource = QGeoPositionInfoSource::createDefaultSource(this);

    if (m_positionSource) {
        connect(m_positionSource, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(positionUpdated(QGeoPositionInfo)));
        connect(m_positionSource, SIGNAL(error(QGeoPositionInfoSource::Error)),
                this, SLOT(positionError(QGeoPositionInfoSource::Error)));
        m_positionSource->setPreferredPositioningMethods(m_positionSource->NonSatellitePositioningMethods);
        m_positionSource->requestUpdate();
    } else {
        emit positionError(QGeoPositionInfoSource::Error());
    }

}

void Position::positionUpdated(QGeoPositionInfo position)
{
   emit getPosition(QString("coord_"+QString::number(position.coordinate().latitude(),'f')+","+QString::number(position.coordinate().longitude(),'f')));
    qDebug()<<"Got coordinate:"<<QString::number(position.coordinate().latitude(),'f');
}

void Position::positionError(QGeoPositionInfoSource::Error /*error*/)
{
    emit getPositionError();
    qDebug() << "Error in getting Position from platform";

}

