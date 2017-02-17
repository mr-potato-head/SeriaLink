#include "comportmanager.h"

ComPortManager::ComPortManager(ComPortSettings *port_settings,
                               QObject *parent)
    : QObject(parent),
      com_port_settings_{port_settings} {
    com_port_ = new LocalComPort();
    com_port_->SetPortSettings(com_port_settings_);

    connect(com_port_, SIGNAL(Receive(QByteArray)),
            this, SIGNAL(Receive(QByteArray)));
}

ComPortManager::~ComPortManager() {
    if(com_port_->IsOpen())
        com_port_->ClosePort();
    delete com_port_;
    com_port_ = NULL;
}

ComPortSettings* ComPortManager::GetPortSettings(void) const {
    return com_port_settings_;
}

void ComPortManager::OpenPort(void) {
    com_port_->OpenPort();
}

void ComPortManager::ClosePort(void) {
    com_port_->ClosePort();
}
