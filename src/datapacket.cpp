#include "datapacket.h"

DataPacket::DataPacket()
{
}

DataPacket::DataPacket(const QByteArray &data)
    : data_{data}
{
  datetime_ = QDateTime::currentDateTime();
}

const QByteArray& DataPacket::GetData(void) const {
    return data_;
}
