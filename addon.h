#ifndef ADDON_H
#define ADDON_H
#include <thread>
#include <QDir>
#include <QString>
#include <string>
#include <QList>
#include <QDebug>
#include "widget.h"
#include "color_change.h"
#include <QDebug>
#include <mutex>

void picture_cycle(const char * src_name);
void getfileList(const char *path);
#endif // ADDON_H
