/*
This file is part of pyOCCT which provides Python bindings to the OpenCASCADE
geometry kernel.

Copyright (C) 2016-2018  Laughlin Research, LLC
Copyright (C) 2019 Trevor Laughlin and the pyOCCT contributors

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <pyOCCT_Common.hxx>
#include <Standard_Transient.hxx>
#include <Standard_Handle.hxx>
#include <TDataStd_HDataMapOfStringHArray1OfInteger.hxx>
#include <Standard_Type.hxx>
#include <Standard_TypeDef.hxx>
#include <TDataStd_DataMapOfStringHArray1OfInteger.hxx>

void bind_TDataStd_HDataMapOfStringHArray1OfInteger(py::module &mod){

py::class_<TDataStd_HDataMapOfStringHArray1OfInteger, opencascade::handle<TDataStd_HDataMapOfStringHArray1OfInteger>, Standard_Transient> cls_TDataStd_HDataMapOfStringHArray1OfInteger(mod, "TDataStd_HDataMapOfStringHArray1OfInteger", "Extension of TDataStd_DataMapOfStringHArray1OfInteger class to be manipulated by handle.");

// Constructors
cls_TDataStd_HDataMapOfStringHArray1OfInteger.def(py::init<>());
cls_TDataStd_HDataMapOfStringHArray1OfInteger.def(py::init<const Standard_Integer>(), py::arg("NbBuckets"));
cls_TDataStd_HDataMapOfStringHArray1OfInteger.def(py::init<const TDataStd_DataMapOfStringHArray1OfInteger &>(), py::arg("theOther"));

// Fields

// Methods
cls_TDataStd_HDataMapOfStringHArray1OfInteger.def_static("get_type_name_", (const char * (*)()) &TDataStd_HDataMapOfStringHArray1OfInteger::get_type_name, "None");
cls_TDataStd_HDataMapOfStringHArray1OfInteger.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &TDataStd_HDataMapOfStringHArray1OfInteger::get_type_descriptor, "None");
cls_TDataStd_HDataMapOfStringHArray1OfInteger.def("DynamicType", (const opencascade::handle<Standard_Type> & (TDataStd_HDataMapOfStringHArray1OfInteger::*)() const) &TDataStd_HDataMapOfStringHArray1OfInteger::DynamicType, "None");
cls_TDataStd_HDataMapOfStringHArray1OfInteger.def("Map", (const TDataStd_DataMapOfStringHArray1OfInteger & (TDataStd_HDataMapOfStringHArray1OfInteger::*)() const) &TDataStd_HDataMapOfStringHArray1OfInteger::Map, "None");
cls_TDataStd_HDataMapOfStringHArray1OfInteger.def("ChangeMap", (TDataStd_DataMapOfStringHArray1OfInteger & (TDataStd_HDataMapOfStringHArray1OfInteger::*)()) &TDataStd_HDataMapOfStringHArray1OfInteger::ChangeMap, "None");

// Enums

}