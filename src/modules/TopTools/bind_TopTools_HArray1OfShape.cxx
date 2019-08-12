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
#include <TopTools_Array1OfShape.hxx>
#include <Standard_Transient.hxx>
#include <Standard.hxx>
#include <Standard_Handle.hxx>
#include <NCollection_BaseAllocator.hxx>
#include <Standard_TypeDef.hxx>
#include <NCollection_Array1.hxx>
#include <TopTools_HArray1OfShape.hxx>
#include <Standard_Type.hxx>

void bind_TopTools_HArray1OfShape(py::module &mod){

py::class_<TopTools_HArray1OfShape, opencascade::handle<TopTools_HArray1OfShape>, Standard_Transient> cls_TopTools_HArray1OfShape(mod, "TopTools_HArray1OfShape", "None", py::multiple_inheritance());

// Constructors
cls_TopTools_HArray1OfShape.def(py::init<const Standard_Integer, const Standard_Integer>(), py::arg("theLower"), py::arg("theUpper"));
cls_TopTools_HArray1OfShape.def(py::init<const Standard_Integer, const Standard_Integer, const TopTools_Array1OfShape::value_type &>(), py::arg("theLower"), py::arg("theUpper"), py::arg("theValue"));
cls_TopTools_HArray1OfShape.def(py::init<const TopTools_Array1OfShape &>(), py::arg("theOther"));

// Fields

// Methods
// cls_TopTools_HArray1OfShape.def_static("operator new_", (void * (*)(size_t)) &TopTools_HArray1OfShape::operator new, "None", py::arg("theSize"));
// cls_TopTools_HArray1OfShape.def_static("operator delete_", (void (*)(void *)) &TopTools_HArray1OfShape::operator delete, "None", py::arg("theAddress"));
// cls_TopTools_HArray1OfShape.def_static("operator new[]_", (void * (*)(size_t)) &TopTools_HArray1OfShape::operator new[], "None", py::arg("theSize"));
// cls_TopTools_HArray1OfShape.def_static("operator delete[]_", (void (*)(void *)) &TopTools_HArray1OfShape::operator delete[], "None", py::arg("theAddress"));
// cls_TopTools_HArray1OfShape.def_static("operator new_", (void * (*)(size_t, void *)) &TopTools_HArray1OfShape::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_TopTools_HArray1OfShape.def_static("operator delete_", (void (*)(void *, void *)) &TopTools_HArray1OfShape::operator delete, "None", py::arg(""), py::arg(""));
// cls_TopTools_HArray1OfShape.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &TopTools_HArray1OfShape::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_TopTools_HArray1OfShape.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &TopTools_HArray1OfShape::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_TopTools_HArray1OfShape.def("Array1", (const TopTools_Array1OfShape & (TopTools_HArray1OfShape::*)() const) &TopTools_HArray1OfShape::Array1, "None");
cls_TopTools_HArray1OfShape.def("ChangeArray1", (TopTools_Array1OfShape & (TopTools_HArray1OfShape::*)()) &TopTools_HArray1OfShape::ChangeArray1, "None");
cls_TopTools_HArray1OfShape.def_static("get_type_name_", (const char * (*)()) &TopTools_HArray1OfShape::get_type_name, "None");
cls_TopTools_HArray1OfShape.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &TopTools_HArray1OfShape::get_type_descriptor, "None");
cls_TopTools_HArray1OfShape.def("DynamicType", (const opencascade::handle<Standard_Type> & (TopTools_HArray1OfShape::*)() const) &TopTools_HArray1OfShape::DynamicType, "None");

// Enums

}