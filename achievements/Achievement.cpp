#include <string>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QTextStream>
#include "Achievement.h"

Achievement::Achievement(std::string path)
    :path(path)
{
	//QFile file(QString::fromStdString(path));
	QFile file(QString::fromStdString("D:/Projects/PacSnake/repo/data/stat.txt"));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "Achievment file error", file.errorString());
    }

    QTextStream in(&file);
    int i = 0;
    while(!in.atEnd()) {
		QString line = in.readLine();
		qDebug() << line;
		qDebug() << std::stoi(line.toStdString());
        switch (i) {
			case 0: update_in_game_distance(std::stoi(line.toStdString())); break;
            case 1: update_survival_time(std::stoi(line.toStdString())); break;
            case 2: update_fruits_eaten(std::stoi(line.toStdString())); break;
            case 3: update_snake_length(std::stoi(line.toStdString())); break;
        }
		i++;
    }

    file.close();
}
/*
void Achievement::update_achievement(int type, int value){
    QFile file(QString::fromStdString(path));
          if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
          {
              //Streaming text to the file
              QTextStream stream(&file);

              //stream << "Center Point: " << iter_result[0] << "  " << iter_result[1]
              //          << "  " << iter_result[2] << " Rotation: " << iter_result[3] <<'\n';
              //
              file.close();
              qDebug() << "Writing finished";
          }
}
*/
