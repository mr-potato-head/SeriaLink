#include "dataformatter.h"

DataFormatter::DataFormatter()
{

}

QString DataFormatter::formatData(const ViewSettings &settings,
                                  const QByteArray& data)
{
    ViewSettings::DataSize eDataSize = settings.GetDataSize();
    ViewSettings::DisplayType eDisplayType = settings.GetDisplayType();

    quint8 quint8_size = 0;
    switch(eDataSize) {
    case ViewSettings::DataSize::k1Byte:
        quint8_size = 1;
        break;
    case ViewSettings::DataSize::k2Bytes:
        quint8_size = 2;
        break;
    case ViewSettings::DataSize::k4Bytes:
        quint8_size = 4;
        break;
    case ViewSettings::DataSize::k8Bytes:
        quint8_size = 8;
        break;
    default:
        quint8_size = 4;
        break;
    }

    QString out;
    quint32 quint32_index = 0;
    quint32 quint32_datasize = data.size();
    for(quint32_index = 0 ; quint32_index < quint32_datasize ; quint32_index+=quint8_size)
    {
        QByteArray dataBlock = data.mid(quint32_index, quint8_size);
        switch (eDisplayType) {
        case ViewSettings::DisplayType::kAscii:
            dataBlock = dataBlock.replace("\r", "\\r");
            dataBlock = dataBlock.replace("\n", "\\n");
            out += "|" + QString(dataBlock);
            break;
        case ViewSettings::DisplayType::kHexa:
            out += "|" + QString(dataBlock.toHex());
            break;
        case ViewSettings::DisplayType::kDec:
        {
            bool coucou = false;
            out += "|" + QString::number(dataBlock.toHex().toUInt(&coucou, 16));
            break;
        }
        default:
            break;
        }
    }
    return out;
}
