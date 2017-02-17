#ifndef DATAPACKET_H
#define DATAPACKET_H

#include <QByteArray>
#include <QDateEdit>

class DataPacket
{
public:
    DataPacket();
    DataPacket(const QByteArray& data);
    const QByteArray& GetData(void) const;
private:
    QByteArray data_;
    QDateTime datetime_;
};

#endif // DATAPACKET_H
