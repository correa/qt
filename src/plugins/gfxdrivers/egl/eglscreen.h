/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Copyright (c) 2012-2013 LG Electronics, Inc.
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef PVREGLSCREEN_H
#define PVREGLSCREEN_H

#include <QScreen>
#include <QGLScreen>

class EglScreen;

//#define ENABLE_TRACE 1
#ifdef ENABLE_TRACE
#define TRACE printf
#else
#define TRACE (void)
#endif


class EglScreenSurfaceFunctions : public QGLScreenSurfaceFunctions
{
public:
    EglScreenSurfaceFunctions(EglScreen *s, int screenNum)
        : screen(s), displayId(screenNum) {}

    bool createNativeWindow(QWidget *widget, EGLNativeWindowType *native);

private:
    EglScreen *screen;
    int displayId;
};

class EglScreen : public QGLScreen
{
public:
    EglScreen(int displayId);
    ~EglScreen();

    bool initDevice();
    bool connect(const QString &displaySpec);
    void disconnect();
    void shutdownDevice();
    void setMode(int, int, int) {}

    void blit(const QImage &img, const QPoint &topLeft, const QRegion &region);
    void solidFill(const QColor &color, const QRegion &region);

    bool chooseContext(QGLContext *context, const QGLContext *shareContext);
    bool hasOpenGL();

    QWSWindowSurface* createSurface(QWidget *widget) const;
	QWSWindowSurface* createSurface(const QString &key) const;

private:
    void sync();

    mutable const QScreen *parent;
};

#endif
