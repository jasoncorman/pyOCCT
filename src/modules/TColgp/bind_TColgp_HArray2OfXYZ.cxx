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
#include <TColgp_Array2OfXYZ.hxx>
#include <Standard_Transient.hxx>
#include <Standard.hxx>
#include <Standard_Handle.hxx>
#include <NCollection_BaseAllocator.hxx>
#include <Standard_TypeDef.hxx>
#include <NCollection_Array2.hxx>
#include <TColgp_HArray2OfXYZ.hxx>
#include <Standard_Type.hxx>

void bind_TColgp_HArray2OfXYZ(py::module &mod){

py::class_<TColgp_HArray2OfXYZ, opencascade::handle<TColgp_HArray2OfXYZ>, Standard_Transient> cls_TColgp_HArray2OfXYZ(mod, "TColgp_HArray2OfXYZ", "None", py::multiple_inheritance());

// Constructors
cls_TColgp_HArray2OfXYZ.def(py::init<const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Integer>(), py::arg("theRowLow"), py::arg("theRowUpp"), py::arg("theColLow"), py::arg("theColUpp"));
cls_TColgp_HArray2OfXYZ.def(py::init<const Standard_Integer, const Standard_Integer, const Standard_Integer, const Standard_Integer, const TColgp_Array2OfXYZ::value_type &>(), py::arg("theRowLow"), py::arg("theRowUpp"), py::arg("theColLow"), py::arg("theColUpp"), py::arg("theValue"));
cls_TColgp_HArray2OfXYZ.def(py::init<const TColgp_Array2OfXYZ &>(), py::arg("theOther"));

// Fields

// Methods
// cls_TColgp_HArray2OfXYZ.def_static("operator new_", (void * (*)(size_t)) &TColgp_HArray2OfXYZ::operator new, "None", py::arg("theSize"));
// cls_TColgp_HArray2OfXYZ.def_static("operator delete_", (void (*)(void *)) &TColgp_HArray2OfXYZ::operator delete, "None", py::arg("theAddress"));
// cls_TColgp_HArray2OfXYZ.def_static("operator new[]_", (void * (*)(size_t)) &TColgp_HArray2OfXYZ::operator new[], "None", py::arg("theSize"));
// cls_TColgp_HArray2OfXYZ.def_static("operator delete[]_", (void (*)(void *)) &TColgp_HArray2OfXYZ::operator delete[], "None", py::arg("theAddress"));
// cls_TColgp_HArray2OfXYZ.def_static("operator new_", (void * (*)(size_t, void *)) &TColgp_HArray2OfXYZ::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_TColgp_HArray2OfXYZ.def_static("operator delete_", (void (*)(void *, void *)) &TColgp_HArray2OfXYZ::operator delete, "None", py::arg(""), py::arg(""));
// cls_TColgp_HArray2OfXYZ.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &TColgp_HArray2OfXYZ::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_TColgp_HArray2OfXYZ.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &TColgp_HArray2OfXYZ::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_TColgp_HArray2OfXYZ.def("Array2", (const TColgp_Array2OfXYZ & (TColgp_HArray2OfXYZ::*)() const) &TColgp_HArray2OfXYZ::Array2, "None");
cls_TColgp_HArray2OfXYZ.def("ChangeArray2", (TColgp_Array2OfXYZ & (TColgp_HArray2OfXYZ::*)()) &TColgp_HArray2OfXYZ::ChangeArray2, "None");
cls_TColgp_HArray2OfXYZ.def_static("get_type_name_", (const char * (*)()) &TColgp_HArray2OfXYZ::get_type_name, "None");
cls_TColgp_HArray2OfXYZ.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &TColgp_HArray2OfXYZ::get_type_descriptor, "None");
cls_TColgp_HArray2OfXYZ.def("DynamicType", (const opencascade::handle<Standard_Type> & (TColgp_HArray2OfXYZ::*)() const) &TColgp_HArray2OfXYZ::DynamicType, "None");

// Enums

}