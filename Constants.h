#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <QStringList>

namespace Config {
    const int DAYS = 5;
    const int SLOTS = 8;
    
    inline QString normalizeBuilding(QString dept) {
        if (dept == "FBS") return "FES";
        if (dept == "DChe" || dept == "DMte") return "FMCE";
        if (dept == "Smgs") return "Brabers";
        if (dept == "DCVE" || dept == "FCSE") return "Academic Block";
        return dept;
    }
}
#endif