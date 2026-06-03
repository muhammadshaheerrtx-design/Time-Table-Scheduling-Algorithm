#ifndef EXCELHANDLER_H
#define EXCELHANDLER_H

#include "xlsxdocument.h"
#include "Models.h"

class ExcelHandler {
public:
    static std::vector<Course> parse(QString path, QString dept) {
        QXlsx::Document xlsx(path);
        std::vector<Course> list;
        
        int startRow = 1;
        // Detect header row (usually contains "Code" or "Course")
        for(int r=1; r<10; ++r) {
            if(xlsx.read(r, 2).toString().contains("Code")) { startRow = r + 1; break; }
        }

        for (int r = startRow; r <= xlsx.dimension().lastRow(); ++r) {
            Course c;
            c.code = xlsx.read(r, 2).toString();
            c.title = xlsx.read(r, 3).toString();
            c.creditHours = xlsx.read(r, 4).toInt();
            c.instructor = xlsx.read(r, 6).toString();
            c.section = xlsx.read(r, 5).toString();
            c.department = dept;
            c.expectedStudents = xlsx.read(r, 7).toInt(); // Fallback for various headers
            if(!c.code.isEmpty()) list.push_back(c);
        }
        return list;
    }
};
#endif