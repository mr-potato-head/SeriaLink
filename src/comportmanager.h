#ifndef COMPORTMANAGER_H
#define COMPORTMANAGER_H

#include <QObject>

#include "comport.h"
#include "localcomport.h"
#include "comportsettings.h"

class ComPortManager : public QObject
{
    Q_OBJECT
public:
    explicit ComPortManager(ComPortSettings* port_settings,
                            QObject* parent = 0);

    ~ComPortManager();

    //! Get port settings
    ComPortSettings* GetPortSettings(void) const;

 signals:
  //! Emitted when new data are received
  void Receive(const DataPacket&);

public slots:
    //! Open COM port
    void OpenPort(void);

    //! Close COM port
    void ClosePort(void);

private:
    //! Associated COM port
    ComPort* com_port_ {NULL};

    //! COM port settings
    ComPortSettings* com_port_settings_ {NULL};
};

#endif // COMPORTMANAGER_H
