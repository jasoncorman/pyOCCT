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
#include <TObj_LabelIterator.hxx>
#include <TDF_Label.hxx>
#include <Standard_Handle.hxx>
#include <Standard_Type.hxx>
#include <Standard_TypeDef.hxx>
#include <TObj_ReferenceIterator.hxx>

void bind_TObj_ReferenceIterator(py::module &mod){

py::class_<TObj_ReferenceIterator, opencascade::handle<TObj_ReferenceIterator>, TObj_LabelIterator> cls_TObj_ReferenceIterator(mod, "TObj_ReferenceIterator", "This class provides an iterator by references of the object (implements TObj_ReferenceIterator interface)");

// Constructors
cls_TObj_ReferenceIterator.def(py::init<const TDF_Label &>(), py::arg("theLabel"));
cls_TObj_ReferenceIterator.def(py::init<const TDF_Label &, const opencascade::handle<Standard_Type> &>(), py::arg("theLabel"), py::arg("theType"));
cls_TObj_ReferenceIterator.def(py::init<const TDF_Label &, const opencascade::handle<Standard_Type> &, const Standard_Boolean>(), py::arg("theLabel"), py::arg("theType"), py::arg("theRecursive"));

// Fields

// Methods
cls_TObj_ReferenceIterator.def_static("get_type_name_", (const char * (*)()) &TObj_ReferenceIterator::get_type_name, "None");
cls_TObj_ReferenceIterator.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &TObj_ReferenceIterator::get_type_descriptor, "None");
cls_TObj_ReferenceIterator.def("DynamicType", (const opencascade::handle<Standard_Type> & (TObj_ReferenceIterator::*)() const) &TObj_ReferenceIterator::DynamicType, "None");

// Enums

}