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
#include <Standard.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <Standard_TypeDef.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <BRepLProp_CurveTool.hxx>

void bind_BRepLProp_CurveTool(py::module &mod){

py::class_<BRepLProp_CurveTool, std::unique_ptr<BRepLProp_CurveTool, Deleter<BRepLProp_CurveTool>>> cls_BRepLProp_CurveTool(mod, "BRepLProp_CurveTool", "None");

// Constructors

// Fields

// Methods
// cls_BRepLProp_CurveTool.def_static("operator new_", (void * (*)(size_t)) &BRepLProp_CurveTool::operator new, "None", py::arg("theSize"));
// cls_BRepLProp_CurveTool.def_static("operator delete_", (void (*)(void *)) &BRepLProp_CurveTool::operator delete, "None", py::arg("theAddress"));
// cls_BRepLProp_CurveTool.def_static("operator new[]_", (void * (*)(size_t)) &BRepLProp_CurveTool::operator new[], "None", py::arg("theSize"));
// cls_BRepLProp_CurveTool.def_static("operator delete[]_", (void (*)(void *)) &BRepLProp_CurveTool::operator delete[], "None", py::arg("theAddress"));
// cls_BRepLProp_CurveTool.def_static("operator new_", (void * (*)(size_t, void *)) &BRepLProp_CurveTool::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepLProp_CurveTool.def_static("operator delete_", (void (*)(void *, void *)) &BRepLProp_CurveTool::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepLProp_CurveTool.def_static("Value_", (void (*)(const BRepAdaptor_Curve &, const Standard_Real, gp_Pnt &)) &BRepLProp_CurveTool::Value, "Computes the point <P> of parameter <U> on the curve <C>.", py::arg("C"), py::arg("U"), py::arg("P"));
cls_BRepLProp_CurveTool.def_static("D1_", (void (*)(const BRepAdaptor_Curve &, const Standard_Real, gp_Pnt &, gp_Vec &)) &BRepLProp_CurveTool::D1, "Computes the point <P> and first derivative <V1> of parameter <U> on the curve <C>.", py::arg("C"), py::arg("U"), py::arg("P"), py::arg("V1"));
cls_BRepLProp_CurveTool.def_static("D2_", (void (*)(const BRepAdaptor_Curve &, const Standard_Real, gp_Pnt &, gp_Vec &, gp_Vec &)) &BRepLProp_CurveTool::D2, "Computes the point <P>, the first derivative <V1> and second derivative <V2> of parameter <U> on the curve <C>.", py::arg("C"), py::arg("U"), py::arg("P"), py::arg("V1"), py::arg("V2"));
cls_BRepLProp_CurveTool.def_static("D3_", (void (*)(const BRepAdaptor_Curve &, const Standard_Real, gp_Pnt &, gp_Vec &, gp_Vec &, gp_Vec &)) &BRepLProp_CurveTool::D3, "Computes the point <P>, the first derivative <V1>, the second derivative <V2> and third derivative <V3> of parameter <U> on the curve <C>.", py::arg("C"), py::arg("U"), py::arg("P"), py::arg("V1"), py::arg("V2"), py::arg("V3"));
cls_BRepLProp_CurveTool.def_static("Continuity_", (Standard_Integer (*)(const BRepAdaptor_Curve &)) &BRepLProp_CurveTool::Continuity, "returns the order of continuity of the curve <C>. returns 1 : first derivative only is computable returns 2 : first and second derivative only are computable. returns 3 : first, second and third are computable.", py::arg("C"));
cls_BRepLProp_CurveTool.def_static("FirstParameter_", (Standard_Real (*)(const BRepAdaptor_Curve &)) &BRepLProp_CurveTool::FirstParameter, "returns the first parameter bound of the curve.", py::arg("C"));
cls_BRepLProp_CurveTool.def_static("LastParameter_", (Standard_Real (*)(const BRepAdaptor_Curve &)) &BRepLProp_CurveTool::LastParameter, "returns the last parameter bound of the curve. FirstParameter must be less than LastParamenter.", py::arg("C"));

// Enums

}