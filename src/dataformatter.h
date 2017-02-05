#ifndef DATAFORMATTER_H
#define DATAFORMATTER_H

#include <QString>
#include <QByteArray>

#include "viewsettings.h"

class DataFormatter
{
public:

    DataFormatter();

    static QString formatData(const ViewSettings& settings,
                              const QByteArray& data);
};

#endif // DATAFORMATTER_H
