/**************************************************************************
** This file is part of LiteIDE
**
** Copyright (c) 2011-2019 LiteIDE. All rights reserved.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** In addition, as a special exception,  that plugins developed for LiteIDE,
** are allowed to remain closed sourced and can be distributed under any license .
** These rights are included in the file LGPL_EXCEPTION.txt in this package.
**
**************************************************************************/
// Module: gdbdebuggerplugin.cpp
// Creator: visualfc <visualfc@gmail.com>

#include "dlvdebuggerplugin.h"
#include "dlvdebugger.h"

#ifdef USE_DLVCLIENT
#include "dlvrpcdebugger.h"
#endif

#include "dlvdebuggeroptionfactory.h"
#include "litedebugapi/litedebugapi.h"

//lite_memory_check_begin
#if defined(WIN32) && defined(_MSC_VER) &&  defined(_DEBUG)
     #define _CRTDBG_MAP_ALLOC
     #include <stdlib.h>
     #include <crtdbg.h>
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
#endif
//lite_memory_check_end

DlvDebuggerPlugin::DlvDebuggerPlugin()
{
}

bool DlvDebuggerPlugin::load(LiteApi::IApplication *app)
{
    LiteApi::IDebuggerManager *manager = LiteApi::getDebugManager(app);
    if (!manager) {
        return false;
    }
#ifdef USE_DLVCLIENT
    DlvDebugger *debug = new DlvDebugger(app);//do not have variable view,stack view...
#else
    DlvRpcDebugger *debug = new DlvRpcDebugger(app);
#endif
    manager->addDebugger(debug);
    manager->setCurrentDebugger(debug);
    app->optionManager()->addFactory(new DlvDebuggerOptionFactory(app,this));
    return true;
}

QStringList DlvDebuggerPlugin::dependPluginList() const
{
    return QStringList() << "plugin/litedebug";
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(PluginFactory,PluginFactory)
#endif
