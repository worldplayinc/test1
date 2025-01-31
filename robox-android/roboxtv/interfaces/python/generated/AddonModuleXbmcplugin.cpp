

/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

// ************************************************************************
// This file was generated by xbmc compile process. DO NOT EDIT!!
//  It was created by running the code generator on the spec file for
//  the module "xbmcplugin" on the template file PythonSwig.template.cpp
// ************************************************************************



#include <Python.h>
#include <string>
#include "interfaces/python/LanguageHook.h"
#include "interfaces/python/swig.h"
#include "interfaces/python/PyContext.h"


#include "interfaces/legacy/ModuleXbmcplugin.h"

using namespace XBMCAddon;
using namespace xbmcplugin;

#if defined(__GNUG__) && (__GNUC__>4) || (__GNUC__==4 && __GNUC_MINOR__>=2)
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif



namespace PythonBindings
{

  //=========================================================================
  // These variables define the type XBMCAddon::xbmcgui::ListItem from another module 
  extern TypeInfo TyXBMCAddon_xbmcgui_ListItem_Type;
  //=========================================================================



  static PyObject* xbmcplugin_addDirectoryItem (PyObject* self  , PyObject *args, PyObject *kwds  )
  {
    XBMC_TRACE;

    static const char *keywords[] = {
          "handle",
          "url",
          "listitem",
          "isFolder",
          "totalItems",
          NULL};
         
    int  handle ;         
    std::string  url ;
    PyObject* pyurl = NULL;         
    XBMCAddon::xbmcgui::ListItem * listitem ;
    PyObject* pylistitem = NULL;         
    bool  isFolder  = false;         
    int  totalItems  = 0;
    if (!PyArg_ParseTupleAndKeywords(
       args,
       kwds,
       (char*)"iOO|bi",
       (char**)keywords,
         &handle,
         &pyurl,
         &pylistitem,
         &isFolder,
         &totalItems
       ))
    {
      return NULL;
    }

    bool  apiResult;
    try
    {
      if (pyurl) PyXBMCGetUnicodeString(url,pyurl,false,"url","XBMCAddon::xbmcplugin::addDirectoryItem"); 
      listitem = (XBMCAddon::xbmcgui::ListItem *)retrieveApiInstance(pylistitem,"p.XBMCAddon::xbmcgui::ListItem","XBMCAddon::xbmcplugin::","XBMCAddon::xbmcplugin::addDirectoryItem"); 

      XBMCAddon::SetLanguageHookGuard slhg(XBMCAddon::Python::PythonLanguageHook::GetIfExists(PyThreadState_Get()->interp).get());
      apiResult = (bool )XBMCAddon::xbmcplugin::addDirectoryItem(  handle,  url,  listitem,  isFolder,  totalItems  );

    }
    catch (const XBMCAddon::WrongTypeException& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_TypeError, e.GetMessage()); 
      return NULL; 
    }
    catch (const XbmcCommons::Exception& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_RuntimeError, e.GetMessage()); 
      return NULL; 
    }
    catch (...)
    {
      CLog::Log(LOGERROR,"EXCEPTION: Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::addDirectoryItem\"");
      PyErr_SetString(PyExc_RuntimeError, "Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::addDirectoryItem\""); 
      return NULL; 
    }

    PyObject* result = Py_None;

    // transform the result
    result = Py_BuildValue((char*)"b", apiResult);

    return result; 
  } 

  static PyObject* xbmcplugin_addDirectoryItems (PyObject* self  , PyObject *args, PyObject *kwds  )
  {
    XBMC_TRACE;

    static const char *keywords[] = {
          "handle",
          "items",
          "totalItems",
          NULL};
         
    int  handle ;         
    std::vector< Tuple< XBMCAddon::String ,XBMCAddon::xbmcgui::ListItem const *,bool  >  >  items ;
    PyObject* pyitems = NULL;         
    int  totalItems  = 0;
    if (!PyArg_ParseTupleAndKeywords(
       args,
       kwds,
       (char*)"iO|i",
       (char**)keywords,
         &handle,
         &pyitems,
         &totalItems
       ))
    {
      return NULL;
    }

    bool  apiResult;
    try
    {
      
    {
      bool isTuple = PyObject_TypeCheck(pyitems,&PyTuple_Type);
      if (!isTuple && !PyObject_TypeCheck(pyitems,&PyList_Type))
        throw WrongTypeException("The parameter \"items\" must be either a Tuple or a List.");

      
      PyObject *pyentry1 = NULL;
      int vecSize = (isTuple ? PyTuple_Size(pyitems) : PyList_Size(pyitems));
      for(int i = 0; i < vecSize; i++)
      {
        pyentry1 = (isTuple ? PyTuple_GetItem(pyitems, i) : PyList_GetItem(pyitems, i));
        Tuple< XBMCAddon::String ,XBMCAddon::xbmcgui::ListItem const *,bool  >  entry1;
        
    {
      bool isTuple = PyObject_TypeCheck(pyentry1,&PyTuple_Type);
      if (!isTuple && !PyObject_TypeCheck(pyentry1,&PyList_Type))
        throw WrongTypeException("The parameter \"entry1\" must be either a Tuple or a List.");
      int vecSize = (isTuple ? PyTuple_Size(pyentry1) : PyList_Size(pyentry1));

      if (vecSize > 0)
      {
        PyObject *pyentry0_2 = NULL;
        pyentry0_2 = (isTuple ? PyTuple_GetItem(pyentry1, 0) : PyList_GetItem(pyentry1, 0));
        std::string  entry0_2;
        if (pyentry0_2) PyXBMCGetUnicodeString(entry0_2,pyentry0_2,false,"entry0_2","XBMCAddon::xbmcplugin::addDirectoryItems");
        entry1.first() = entry0_2;
      }

      if (vecSize > 1)
      {
        PyObject *pyentry1_2 = NULL;
        pyentry1_2 = (isTuple ? PyTuple_GetItem(pyentry1, 1) : PyList_GetItem(pyentry1, 1));
        XBMCAddon::xbmcgui::ListItem * entry1_2;
        entry1_2 = (XBMCAddon::xbmcgui::ListItem *)retrieveApiInstance(pyentry1_2,"p.XBMCAddon::xbmcgui::ListItem","XBMCAddon::xbmcplugin::","XBMCAddon::xbmcplugin::addDirectoryItems");
        entry1.second() = entry1_2;
      }

      if (vecSize > 2)
      {
        PyObject *pyentry2_2 = NULL;
        pyentry2_2 = (isTuple ? PyTuple_GetItem(pyentry1, 2) : PyList_GetItem(pyentry1, 2));
        bool  entry2_2;
        entry2_2 = (PyInt_AsLong(pyentry2_2) == 0L ? false : true);
        entry1.third() = entry2_2;
      }

    }
        items.push_back(entry1);
      }
    } 

      XBMCAddon::SetLanguageHookGuard slhg(XBMCAddon::Python::PythonLanguageHook::GetIfExists(PyThreadState_Get()->interp).get());
      apiResult = (bool )XBMCAddon::xbmcplugin::addDirectoryItems(  handle,  items,  totalItems  );

    }
    catch (const XBMCAddon::WrongTypeException& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_TypeError, e.GetMessage()); 
      return NULL; 
    }
    catch (const XbmcCommons::Exception& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_RuntimeError, e.GetMessage()); 
      return NULL; 
    }
    catch (...)
    {
      CLog::Log(LOGERROR,"EXCEPTION: Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::addDirectoryItems\"");
      PyErr_SetString(PyExc_RuntimeError, "Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::addDirectoryItems\""); 
      return NULL; 
    }

    PyObject* result = Py_None;

    // transform the result
    result = Py_BuildValue((char*)"b", apiResult);

    return result; 
  } 

  static PyObject* xbmcplugin_endOfDirectory (PyObject* self  , PyObject *args, PyObject *kwds  )
  {
    XBMC_TRACE;

    static const char *keywords[] = {
          "handle",
          "succeeded",
          "updateListing",
          "cacheToDisc",
          NULL};
         
    int  handle ;         
    bool  succeeded  = true;         
    bool  updateListing  = false;         
    bool  cacheToDisc  = true;
    if (!PyArg_ParseTupleAndKeywords(
       args,
       kwds,
       (char*)"i|bbb",
       (char**)keywords,
         &handle,
         &succeeded,
         &updateListing,
         &cacheToDisc
       ))
    {
      return NULL;
    }


    try
    {

      XBMCAddon::SetLanguageHookGuard slhg(XBMCAddon::Python::PythonLanguageHook::GetIfExists(PyThreadState_Get()->interp).get());
      XBMCAddon::xbmcplugin::endOfDirectory(  handle,  succeeded,  updateListing,  cacheToDisc  );

    }
    catch (const XBMCAddon::WrongTypeException& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_TypeError, e.GetMessage()); 
      return NULL; 
    }
    catch (const XbmcCommons::Exception& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_RuntimeError, e.GetMessage()); 
      return NULL; 
    }
    catch (...)
    {
      CLog::Log(LOGERROR,"EXCEPTION: Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::endOfDirectory\"");
      PyErr_SetString(PyExc_RuntimeError, "Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::endOfDirectory\""); 
      return NULL; 
    }

    PyObject* result = Py_None;

    // transform the result
    Py_INCREF(Py_None);
    result = Py_None;

    return result; 
  } 

  static PyObject* xbmcplugin_setResolvedUrl (PyObject* self  , PyObject *args, PyObject *kwds  )
  {
    XBMC_TRACE;

    static const char *keywords[] = {
          "handle",
          "succeeded",
          "listitem",
          NULL};
         
    int  handle ;         
    bool  succeeded ;         
    XBMCAddon::xbmcgui::ListItem * listitem ;
    PyObject* pylistitem = NULL;
    if (!PyArg_ParseTupleAndKeywords(
       args,
       kwds,
       (char*)"ibO",
       (char**)keywords,
         &handle,
         &succeeded,
         &pylistitem
       ))
    {
      return NULL;
    }


    try
    {
      listitem = (XBMCAddon::xbmcgui::ListItem *)retrieveApiInstance(pylistitem,"p.XBMCAddon::xbmcgui::ListItem","XBMCAddon::xbmcplugin::","XBMCAddon::xbmcplugin::setResolvedUrl"); 

      XBMCAddon::SetLanguageHookGuard slhg(XBMCAddon::Python::PythonLanguageHook::GetIfExists(PyThreadState_Get()->interp).get());
      XBMCAddon::xbmcplugin::setResolvedUrl(  handle,  succeeded,  listitem  );

    }
    catch (const XBMCAddon::WrongTypeException& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_TypeError, e.GetMessage()); 
      return NULL; 
    }
    catch (const XbmcCommons::Exception& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_RuntimeError, e.GetMessage()); 
      return NULL; 
    }
    catch (...)
    {
      CLog::Log(LOGERROR,"EXCEPTION: Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::setResolvedUrl\"");
      PyErr_SetString(PyExc_RuntimeError, "Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::setResolvedUrl\""); 
      return NULL; 
    }

    PyObject* result = Py_None;

    // transform the result
    Py_INCREF(Py_None);
    result = Py_None;

    return result; 
  } 

  static PyObject* xbmcplugin_addSortMethod (PyObject* self  , PyObject *args, PyObject *kwds  )
  {
    XBMC_TRACE;

    static const char *keywords[] = {
          "handle",
          "sortMethod",
          "label2Mask",
          NULL};
         
    int  handle ;         
    int  sortMethod ;         
    std::string  label2Mask  = XBMCAddon::emptyString;
    PyObject* pylabel2Mask = NULL;
    if (!PyArg_ParseTupleAndKeywords(
       args,
       kwds,
       (char*)"ii|O",
       (char**)keywords,
         &handle,
         &sortMethod,
         &pylabel2Mask
       ))
    {
      return NULL;
    }


    try
    {
      if (pylabel2Mask) PyXBMCGetUnicodeString(label2Mask,pylabel2Mask,false,"label2Mask","XBMCAddon::xbmcplugin::addSortMethod"); 

      XBMCAddon::SetLanguageHookGuard slhg(XBMCAddon::Python::PythonLanguageHook::GetIfExists(PyThreadState_Get()->interp).get());
      XBMCAddon::xbmcplugin::addSortMethod(  handle,  sortMethod,  label2Mask  );

    }
    catch (const XBMCAddon::WrongTypeException& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_TypeError, e.GetMessage()); 
      return NULL; 
    }
    catch (const XbmcCommons::Exception& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_RuntimeError, e.GetMessage()); 
      return NULL; 
    }
    catch (...)
    {
      CLog::Log(LOGERROR,"EXCEPTION: Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::addSortMethod\"");
      PyErr_SetString(PyExc_RuntimeError, "Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::addSortMethod\""); 
      return NULL; 
    }

    PyObject* result = Py_None;

    // transform the result
    Py_INCREF(Py_None);
    result = Py_None;

    return result; 
  } 

  static PyObject* xbmcplugin_getSetting (PyObject* self  , PyObject *args, PyObject *kwds  )
  {
    XBMC_TRACE;

    static const char *keywords[] = {
          "handle",
          "id",
          NULL};
         
    int  handle ;         
    char * id ;
    if (!PyArg_ParseTupleAndKeywords(
       args,
       kwds,
       (char*)"is",
       (char**)keywords,
         &handle,
         &id
       ))
    {
      return NULL;
    }

    std::string  apiResult;
    try
    {

      XBMCAddon::SetLanguageHookGuard slhg(XBMCAddon::Python::PythonLanguageHook::GetIfExists(PyThreadState_Get()->interp).get());
      apiResult = (std::string )XBMCAddon::xbmcplugin::getSetting(  handle,  id  );

    }
    catch (const XBMCAddon::WrongTypeException& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_TypeError, e.GetMessage()); 
      return NULL; 
    }
    catch (const XbmcCommons::Exception& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_RuntimeError, e.GetMessage()); 
      return NULL; 
    }
    catch (...)
    {
      CLog::Log(LOGERROR,"EXCEPTION: Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::getSetting\"");
      PyErr_SetString(PyExc_RuntimeError, "Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::getSetting\""); 
      return NULL; 
    }

    PyObject* result = Py_None;

    // transform the result
    result = PyString_FromStringAndSize(apiResult.c_str(), apiResult.length());

    return result; 
  } 

  static PyObject* xbmcplugin_setSetting (PyObject* self  , PyObject *args, PyObject *kwds  )
  {
    XBMC_TRACE;

    static const char *keywords[] = {
          "handle",
          "id",
          "value",
          NULL};
         
    int  handle ;         
    std::string  id ;
    PyObject* pyid = NULL;         
    std::string  value ;
    PyObject* pyvalue = NULL;
    if (!PyArg_ParseTupleAndKeywords(
       args,
       kwds,
       (char*)"iOO",
       (char**)keywords,
         &handle,
         &pyid,
         &pyvalue
       ))
    {
      return NULL;
    }


    try
    {
      if (pyid) PyXBMCGetUnicodeString(id,pyid,false,"id","XBMCAddon::xbmcplugin::setSetting"); 
      if (pyvalue) PyXBMCGetUnicodeString(value,pyvalue,false,"value","XBMCAddon::xbmcplugin::setSetting"); 

      XBMCAddon::SetLanguageHookGuard slhg(XBMCAddon::Python::PythonLanguageHook::GetIfExists(PyThreadState_Get()->interp).get());
      XBMCAddon::xbmcplugin::setSetting(  handle,  id,  value  );

    }
    catch (const XBMCAddon::WrongTypeException& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_TypeError, e.GetMessage()); 
      return NULL; 
    }
    catch (const XbmcCommons::Exception& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_RuntimeError, e.GetMessage()); 
      return NULL; 
    }
    catch (...)
    {
      CLog::Log(LOGERROR,"EXCEPTION: Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::setSetting\"");
      PyErr_SetString(PyExc_RuntimeError, "Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::setSetting\""); 
      return NULL; 
    }

    PyObject* result = Py_None;

    // transform the result
    Py_INCREF(Py_None);
    result = Py_None;

    return result; 
  } 

  static PyObject* xbmcplugin_setContent (PyObject* self  , PyObject *args, PyObject *kwds  )
  {
    XBMC_TRACE;

    static const char *keywords[] = {
          "handle",
          "content",
          NULL};
         
    int  handle ;         
    char * content ;
    if (!PyArg_ParseTupleAndKeywords(
       args,
       kwds,
       (char*)"is",
       (char**)keywords,
         &handle,
         &content
       ))
    {
      return NULL;
    }


    try
    {

      XBMCAddon::SetLanguageHookGuard slhg(XBMCAddon::Python::PythonLanguageHook::GetIfExists(PyThreadState_Get()->interp).get());
      XBMCAddon::xbmcplugin::setContent(  handle,  content  );

    }
    catch (const XBMCAddon::WrongTypeException& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_TypeError, e.GetMessage()); 
      return NULL; 
    }
    catch (const XbmcCommons::Exception& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_RuntimeError, e.GetMessage()); 
      return NULL; 
    }
    catch (...)
    {
      CLog::Log(LOGERROR,"EXCEPTION: Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::setContent\"");
      PyErr_SetString(PyExc_RuntimeError, "Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::setContent\""); 
      return NULL; 
    }

    PyObject* result = Py_None;

    // transform the result
    Py_INCREF(Py_None);
    result = Py_None;

    return result; 
  } 

  static PyObject* xbmcplugin_setPluginCategory (PyObject* self  , PyObject *args, PyObject *kwds  )
  {
    XBMC_TRACE;

    static const char *keywords[] = {
          "handle",
          "category",
          NULL};
         
    int  handle ;         
    std::string  category ;
    PyObject* pycategory = NULL;
    if (!PyArg_ParseTupleAndKeywords(
       args,
       kwds,
       (char*)"iO",
       (char**)keywords,
         &handle,
         &pycategory
       ))
    {
      return NULL;
    }


    try
    {
      if (pycategory) PyXBMCGetUnicodeString(category,pycategory,false,"category","XBMCAddon::xbmcplugin::setPluginCategory"); 

      XBMCAddon::SetLanguageHookGuard slhg(XBMCAddon::Python::PythonLanguageHook::GetIfExists(PyThreadState_Get()->interp).get());
      XBMCAddon::xbmcplugin::setPluginCategory(  handle,  category  );

    }
    catch (const XBMCAddon::WrongTypeException& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_TypeError, e.GetMessage()); 
      return NULL; 
    }
    catch (const XbmcCommons::Exception& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_RuntimeError, e.GetMessage()); 
      return NULL; 
    }
    catch (...)
    {
      CLog::Log(LOGERROR,"EXCEPTION: Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::setPluginCategory\"");
      PyErr_SetString(PyExc_RuntimeError, "Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::setPluginCategory\""); 
      return NULL; 
    }

    PyObject* result = Py_None;

    // transform the result
    Py_INCREF(Py_None);
    result = Py_None;

    return result; 
  } 

  static PyObject* xbmcplugin_setPluginFanart (PyObject* self  , PyObject *args, PyObject *kwds  )
  {
    XBMC_TRACE;

    static const char *keywords[] = {
          "handle",
          "image",
          "color1",
          "color2",
          "color3",
          NULL};
         
    int  handle ;         
    char * image  = NULL;         
    char * color1  = NULL;         
    char * color2  = NULL;         
    char * color3  = NULL;
    if (!PyArg_ParseTupleAndKeywords(
       args,
       kwds,
       (char*)"i|ssss",
       (char**)keywords,
         &handle,
         &image,
         &color1,
         &color2,
         &color3
       ))
    {
      return NULL;
    }


    try
    {

      XBMCAddon::SetLanguageHookGuard slhg(XBMCAddon::Python::PythonLanguageHook::GetIfExists(PyThreadState_Get()->interp).get());
      XBMCAddon::xbmcplugin::setPluginFanart(  handle,  image,  color1,  color2,  color3  );

    }
    catch (const XBMCAddon::WrongTypeException& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_TypeError, e.GetMessage()); 
      return NULL; 
    }
    catch (const XbmcCommons::Exception& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_RuntimeError, e.GetMessage()); 
      return NULL; 
    }
    catch (...)
    {
      CLog::Log(LOGERROR,"EXCEPTION: Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::setPluginFanart\"");
      PyErr_SetString(PyExc_RuntimeError, "Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::setPluginFanart\""); 
      return NULL; 
    }

    PyObject* result = Py_None;

    // transform the result
    Py_INCREF(Py_None);
    result = Py_None;

    return result; 
  } 

  static PyObject* xbmcplugin_setProperty (PyObject* self  , PyObject *args, PyObject *kwds  )
  {
    XBMC_TRACE;

    static const char *keywords[] = {
          "handle",
          "key",
          "value",
          NULL};
         
    int  handle ;         
    char * key ;         
    std::string  value ;
    PyObject* pyvalue = NULL;
    if (!PyArg_ParseTupleAndKeywords(
       args,
       kwds,
       (char*)"isO",
       (char**)keywords,
         &handle,
         &key,
         &pyvalue
       ))
    {
      return NULL;
    }


    try
    {
      if (pyvalue) PyXBMCGetUnicodeString(value,pyvalue,false,"value","XBMCAddon::xbmcplugin::setProperty"); 

      XBMCAddon::SetLanguageHookGuard slhg(XBMCAddon::Python::PythonLanguageHook::GetIfExists(PyThreadState_Get()->interp).get());
      XBMCAddon::xbmcplugin::setProperty(  handle,  key,  value  );

    }
    catch (const XBMCAddon::WrongTypeException& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_TypeError, e.GetMessage()); 
      return NULL; 
    }
    catch (const XbmcCommons::Exception& e)
    { 
      CLog::Log(LOGERROR,"EXCEPTION: %s",e.GetMessage());
      PyErr_SetString(PyExc_RuntimeError, e.GetMessage()); 
      return NULL; 
    }
    catch (...)
    {
      CLog::Log(LOGERROR,"EXCEPTION: Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::setProperty\"");
      PyErr_SetString(PyExc_RuntimeError, "Unknown exception thrown from the call \"XBMCAddon::xbmcplugin::setProperty\""); 
      return NULL; 
    }

    PyObject* result = Py_None;

    // transform the result
    Py_INCREF(Py_None);
    result = Py_None;

    return result; 
  } 


  static PyMethodDef xbmcplugin_methods[] = { 
    {(char*)"addDirectoryItem", (PyCFunction)xbmcplugin_addDirectoryItem, METH_VARARGS|METH_KEYWORDS, NULL }, 
    {(char*)"addDirectoryItems", (PyCFunction)xbmcplugin_addDirectoryItems, METH_VARARGS|METH_KEYWORDS, NULL }, 
    {(char*)"endOfDirectory", (PyCFunction)xbmcplugin_endOfDirectory, METH_VARARGS|METH_KEYWORDS, NULL }, 
    {(char*)"setResolvedUrl", (PyCFunction)xbmcplugin_setResolvedUrl, METH_VARARGS|METH_KEYWORDS, NULL }, 
    {(char*)"addSortMethod", (PyCFunction)xbmcplugin_addSortMethod, METH_VARARGS|METH_KEYWORDS, NULL }, 
    {(char*)"getSetting", (PyCFunction)xbmcplugin_getSetting, METH_VARARGS|METH_KEYWORDS, NULL }, 
    {(char*)"setSetting", (PyCFunction)xbmcplugin_setSetting, METH_VARARGS|METH_KEYWORDS, NULL }, 
    {(char*)"setContent", (PyCFunction)xbmcplugin_setContent, METH_VARARGS|METH_KEYWORDS, NULL }, 
    {(char*)"setPluginCategory", (PyCFunction)xbmcplugin_setPluginCategory, METH_VARARGS|METH_KEYWORDS, NULL }, 
    {(char*)"setPluginFanart", (PyCFunction)xbmcplugin_setPluginFanart, METH_VARARGS|METH_KEYWORDS, NULL }, 
    {(char*)"setProperty", (PyCFunction)xbmcplugin_setProperty, METH_VARARGS|METH_KEYWORDS, NULL }, 
    {NULL, NULL, 0, NULL}
  };

  // This is the call that will call all of the other initializes 
  //  for all of the classes in this module
  static void initTypes()
  {
    static bool typesAlreadyInitialized = false;
    if (!typesAlreadyInitialized)
    {
      typesAlreadyInitialized = true;

    }
  }

  void initModule_xbmcplugin()
  {
    initTypes();

    // init general xbmcplugin modules
    PyObject* module;



    module = Py_InitModule((char*)"xbmcplugin", xbmcplugin_methods);
    if (module == NULL) return;



   // constants
   PyModule_AddStringConstant(module, (char*)"__author__", (char*)"Team Kodi <http://kodi.tv>");
   PyModule_AddStringConstant(module, (char*)"__date__", (char*)"Thu Jan 14 02:05:48 EST 2016");
   PyModule_AddStringConstant(module, (char*)"__version__", (char*)"2.25.0");
   PyModule_AddStringConstant(module, (char*)"__credits__", (char*)"Team Kodi");
   PyModule_AddStringConstant(module, (char*)"__platform__", (char*)"ALL");

   // need to handle constants

   PyModule_AddIntConstant(module,"SORT_METHOD_NONE",SORT_METHOD_NONE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_LABEL",SORT_METHOD_LABEL); 
   PyModule_AddIntConstant(module,"SORT_METHOD_LABEL_IGNORE_THE",SORT_METHOD_LABEL_IGNORE_THE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_DATE",SORT_METHOD_DATE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_SIZE",SORT_METHOD_SIZE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_FILE",SORT_METHOD_FILE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_DRIVE_TYPE",SORT_METHOD_DRIVE_TYPE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_TRACKNUM",SORT_METHOD_TRACKNUM); 
   PyModule_AddIntConstant(module,"SORT_METHOD_DURATION",SORT_METHOD_DURATION); 
   PyModule_AddIntConstant(module,"SORT_METHOD_TITLE",SORT_METHOD_TITLE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_TITLE_IGNORE_THE",SORT_METHOD_TITLE_IGNORE_THE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_ARTIST",SORT_METHOD_ARTIST); 
   PyModule_AddIntConstant(module,"SORT_METHOD_ARTIST_IGNORE_THE",SORT_METHOD_ARTIST_IGNORE_THE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_ALBUM",SORT_METHOD_ALBUM); 
   PyModule_AddIntConstant(module,"SORT_METHOD_ALBUM_IGNORE_THE",SORT_METHOD_ALBUM_IGNORE_THE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_GENRE",SORT_METHOD_GENRE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_VIDEO_YEAR",SORT_METHOD_YEAR); 
   PyModule_AddIntConstant(module,"SORT_METHOD_VIDEO_RATING",SORT_METHOD_VIDEO_RATING); 
   PyModule_AddIntConstant(module,"SORT_METHOD_PROGRAM_COUNT",SORT_METHOD_PROGRAM_COUNT); 
   PyModule_AddIntConstant(module,"SORT_METHOD_PLAYLIST_ORDER",SORT_METHOD_PLAYLIST_ORDER); 
   PyModule_AddIntConstant(module,"SORT_METHOD_EPISODE",SORT_METHOD_EPISODE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_VIDEO_TITLE",SORT_METHOD_VIDEO_TITLE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_VIDEO_SORT_TITLE",SORT_METHOD_VIDEO_SORT_TITLE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_VIDEO_SORT_TITLE_IGNORE_THE",SORT_METHOD_VIDEO_SORT_TITLE_IGNORE_THE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_PRODUCTIONCODE",SORT_METHOD_PRODUCTIONCODE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_SONG_RATING",SORT_METHOD_SONG_RATING); 
   PyModule_AddIntConstant(module,"SORT_METHOD_MPAA_RATING",SORT_METHOD_MPAA_RATING); 
   PyModule_AddIntConstant(module,"SORT_METHOD_VIDEO_RUNTIME",SORT_METHOD_VIDEO_RUNTIME); 
   PyModule_AddIntConstant(module,"SORT_METHOD_STUDIO",SORT_METHOD_STUDIO); 
   PyModule_AddIntConstant(module,"SORT_METHOD_STUDIO_IGNORE_THE",SORT_METHOD_STUDIO_IGNORE_THE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_UNSORTED",SORT_METHOD_UNSORTED); 
   PyModule_AddIntConstant(module,"SORT_METHOD_BITRATE",SORT_METHOD_BITRATE); 
   PyModule_AddIntConstant(module,"SORT_METHOD_LISTENERS",SORT_METHOD_LISTENERS); 
   PyModule_AddIntConstant(module,"SORT_METHOD_COUNTRY",SORT_METHOD_COUNTRY); 
   PyModule_AddIntConstant(module,"SORT_METHOD_DATEADDED",SORT_METHOD_DATEADDED); 
   PyModule_AddIntConstant(module,"SORT_METHOD_FULLPATH",SORT_METHOD_FULLPATH); 
   PyModule_AddIntConstant(module,"SORT_METHOD_LABEL_IGNORE_FOLDERS",SORT_METHOD_LABEL_IGNORE_FOLDERS); 
   PyModule_AddIntConstant(module,"SORT_METHOD_LASTPLAYED",SORT_METHOD_LASTPLAYED); 
   PyModule_AddIntConstant(module,"SORT_METHOD_PLAYCOUNT",SORT_METHOD_PLAYCOUNT); 
   PyModule_AddIntConstant(module,"SORT_METHOD_CHANNEL",SORT_METHOD_CHANNEL); 
   PyModule_AddIntConstant(module,"SORT_METHOD_DATE_TAKEN",SORT_METHOD_DATE_TAKEN); 
   PyModule_AddIntConstant(module,"SORT_METHOD_VIDEO_USER_RATING",SORT_METHOD_VIDEO_USER_RATING); 
   PyModule_AddIntConstant(module,"SORT_METHOD_SONG_USER_RATING",SORT_METHOD_SONG_USER_RATING); 
  }

} // end PythonBindings namespace for python type definitions


