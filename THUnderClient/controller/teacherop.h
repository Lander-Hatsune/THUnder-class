#pragma once
#include <QByteArray>
#include "../definitions.h"
#include "../model/teacherclient.h"

class Teacherop {
private:
    Teacherclient* teacherclient;
    
public:
    Teacherop(Teacherclient*);
    ~Teacherop();
    Teacherop(const Teacherop&) = delete;
    Teacherop& operator = (const Teacherop&) = delete;
    
    void send_audiopiece(string&);
    QByteArray receive_audiopiece();
};
