#pragma once
#include <QVector>

struct Path
{
	QVector<QVector<int>>p;
	int type;
};

void import_path();
void import_path2();