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
#include <BRepPrim_Revolution.hxx>
#include <Standard.hxx>
#include <gp_Ax2.hxx>
#include <Standard_TypeDef.hxx>
#include <gp_Pnt.hxx>
#include <TopoDS_Face.hxx>
#include <BRepPrim_Torus.hxx>

void bind_BRepPrim_Torus(py::module &mod){

py::class_<BRepPrim_Torus, std::unique_ptr<BRepPrim_Torus, Deleter<BRepPrim_Torus>>, BRepPrim_Revolution> cls_BRepPrim_Torus(mod, "BRepPrim_Torus", "Implements the torus primitive");

// Constructors
cls_BRepPrim_Torus.def(py::init<const gp_Ax2 &, const Standard_Real, const Standard_Real>(), py::arg("Position"), py::arg("Major"), py::arg("Minor"));
cls_BRepPrim_Torus.def(py::init<const Standard_Real, const Standard_Real>(), py::arg("Major"), py::arg("Minor"));
cls_BRepPrim_Torus.def(py::init<const gp_Pnt &, const Standard_Real, const Standard_Real>(), py::arg("Center"), py::arg("Major"), py::arg("Minor"));

// Fields

// Methods
// cls_BRepPrim_Torus.def_static("operator new_", (void * (*)(size_t)) &BRepPrim_Torus::operator new, "None", py::arg("theSize"));
// cls_BRepPrim_Torus.def_static("operator delete_", (void (*)(void *)) &BRepPrim_Torus::operator delete, "None", py::arg("theAddress"));
// cls_BRepPrim_Torus.def_static("operator new[]_", (void * (*)(size_t)) &BRepPrim_Torus::operator new[], "None", py::arg("theSize"));
// cls_BRepPrim_Torus.def_static("operator delete[]_", (void (*)(void *)) &BRepPrim_Torus::operator delete[], "None", py::arg("theAddress"));
// cls_BRepPrim_Torus.def_static("operator new_", (void * (*)(size_t, void *)) &BRepPrim_Torus::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepPrim_Torus.def_static("operator delete_", (void (*)(void *, void *)) &BRepPrim_Torus::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepPrim_Torus.def("MakeEmptyLateralFace", (TopoDS_Face (BRepPrim_Torus::*)() const) &BRepPrim_Torus::MakeEmptyLateralFace, "The surface normal should be directed towards the outside.");

// Enums

}