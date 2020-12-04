#include <string>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QTextStream>
#include "Achievement.h"

Achievement::Achievement(std::string path)
    :path(path)
{
    QFile file(QString::fromStdString(path));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "Achievment file error", file.errorString());
    }

    QTextStream in(&file);
    int i = 0;
    while(!in.atEnd()) {
        QString line = in.readLine();
        //QStringList fields = line.split("\n");
        //qDebug() << line;
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

void Achievement::update_achievement(int type, int value){
    QFile file(QString::fromStdString(path));
          if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
          {

              //Streaming text to the file
              QTextStream stream(&writefile);

              stream << get_ingame_distance() << endl << get_survival_time() << get_fruits_eaten() << endl << get_longest_snake_length() << endl << get_play_count();
              //stream << "Center Point: " << iter_result[0] << "  " << iter_result[1]
              //          << "  " << iter_result[2] << " Rotation: " << iter_result[3] <<'\n';
              //
              writefile.close();
              qDebug() << "Writing finished";

}


void Achievement::compare_stat(Stats temp){
    if (temp.get_ingame_distance() > this->get_ingame_distance()){
        this->update_in_game_distance(temp.get_ingame_distance());
    }
    if (temp.get_survival_time() > this->get_survival_time()){
        this->update_survival_time(temp.get_survival_time());
    }
    if (temp.get_fruits_eaten() > this->get_fruits_eaten()){
        this->update_fruits_eaten(temp.get_fruits_eaten());
    }
    if (temp.get_longest_snake_length() > this->get_longest_snake_length()){
        this->update_snake_length(temp.get_longest_snake_length());
    }
    if (temp.get_play_count() > this->get_play_count()){
        this->update_play_count(temp.get_play_count());
    }
}

