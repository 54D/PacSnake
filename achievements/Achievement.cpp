#include <string>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QTextStream>
#include "Achievement.h"

Achievement::Achievement(std::string path)
    :path(path)
{
    //check and create file if not exist
    QFileInfo check_file(QString::fromStdString(path));
    if (!(check_file.exists() && check_file.isFile())) {
        QFile createFile(QString::fromStdString(path));
        createFile.open(QIODevice::WriteOnly);
        QTextStream stream(&createFile);
        stream << "0" << endl << "0" << endl << "0" << endl << "0" << endl << "0" << endl;
        createFile.close();
    }
    //read file
    QFile file(QString::fromStdString(path));
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
            case 4: update_play_count(std::stoi(line.toStdString())); break;
        }
		i++;
    }

    file.close();
}

void Achievement::update_achievement_file(){
    QFile writefile(QString::fromStdString(path));
    writefile.open(QFile::WriteOnly);
    //Streaming text to the file
    QTextStream stream(&writefile);
    stream << get_ingame_distance() << endl << get_survival_time() << endl << get_fruits_eaten() << endl << get_longest_snake_length() << endl << get_play_count();
    //qDebug() << get_ingame_distance() << get_survival_time() << get_fruits_eaten();
    writefile.close();
    qDebug() << "Writing file finished";
}

void Achievement::compare_stat(Stats temp){
    if (temp.get_survival_time() > this->get_survival_time()){
        this->update_survival_time(temp.get_survival_time());
    }
    if (temp.get_fruits_eaten() > this->get_fruits_eaten()){
        this->update_fruits_eaten(temp.get_fruits_eaten());
    }
    if (temp.get_longest_snake_length() > this->get_longest_snake_length()){
        this->update_snake_length(temp.get_longest_snake_length());
    }
}
