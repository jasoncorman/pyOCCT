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
#include <Blend_SurfPointFuncInv.hxx>
#include <Standard.hxx>
#include <Standard_Handle.hxx>
#include <Adaptor3d_HSurface.hxx>
#include <Adaptor3d_HCurve.hxx>
#include <Law_Function.hxx>
#include <Standard_TypeDef.hxx>
#include <math_Vector.hxx>
#include <math_Matrix.hxx>
#include <gp_Pnt.hxx>
#include <BRepBlend_SurfPointEvolRadInv.hxx>

void bind_BRepBlend_SurfPointEvolRadInv(py::module &mod){

py::class_<BRepBlend_SurfPointEvolRadInv, std::unique_ptr<BRepBlend_SurfPointEvolRadInv, Deleter<BRepBlend_SurfPointEvolRadInv>>, Blend_SurfPointFuncInv> cls_BRepBlend_SurfPointEvolRadInv(mod, "BRepBlend_SurfPointEvolRadInv", "Function of reframing between a point and a surface. This function is used to find a solution on a done point of the curve when using SurfRstConsRad or CSConstRad... The vector <X> used in Value, Values and Derivatives methods has to be the vector of the parametric coordinates w, U, V where w is the parameter on the guide line, U,V are the parametric coordinates of a point on the partner surface.");

// Constructors
cls_BRepBlend_SurfPointEvolRadInv.def(py::init<const opencascade::handle<Adaptor3d_HSurface> &, const opencascade::handle<Adaptor3d_HCurve> &, const opencascade::handle<Law_Function> &>(), py::arg("S"), py::arg("C"), py::arg("Evol"));

// Fields

// Methods
// cls_BRepBlend_SurfPointEvolRadInv.def_static("operator new_", (void * (*)(size_t)) &BRepBlend_SurfPointEvolRadInv::operator new, "None", py::arg("theSize"));
// cls_BRepBlend_SurfPointEvolRadInv.def_static("operator delete_", (void (*)(void *)) &BRepBlend_SurfPointEvolRadInv::operator delete, "None", py::arg("theAddress"));
// cls_BRepBlend_SurfPointEvolRadInv.def_static("operator new[]_", (void * (*)(size_t)) &BRepBlend_SurfPointEvolRadInv::operator new[], "None", py::arg("theSize"));
// cls_BRepBlend_SurfPointEvolRadInv.def_static("operator delete[]_", (void (*)(void *)) &BRepBlend_SurfPointEvolRadInv::operator delete[], "None", py::arg("theAddress"));
// cls_BRepBlend_SurfPointEvolRadInv.def_static("operator new_", (void * (*)(size_t, void *)) &BRepBlend_SurfPointEvolRadInv::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_BRepBlend_SurfPointEvolRadInv.def_static("operator delete_", (void (*)(void *, void *)) &BRepBlend_SurfPointEvolRadInv::operator delete, "None", py::arg(""), py::arg(""));
cls_BRepBlend_SurfPointEvolRadInv.def("Set", (void (BRepBlend_SurfPointEvolRadInv::*)(const Standard_Integer)) &BRepBlend_SurfPointEvolRadInv::Set, "None", py::arg("Choix"));
cls_BRepBlend_SurfPointEvolRadInv.def("NbEquations", (Standard_Integer (BRepBlend_SurfPointEvolRadInv::*)() const) &BRepBlend_SurfPointEvolRadInv::NbEquations, "returns 3.");
cls_BRepBlend_SurfPointEvolRadInv.def("Value", (Standard_Boolean (BRepBlend_SurfPointEvolRadInv::*)(const math_Vector &, math_Vector &)) &BRepBlend_SurfPointEvolRadInv::Value, "computes the values <F> of the Functions for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"));
cls_BRepBlend_SurfPointEvolRadInv.def("Derivatives", (Standard_Boolean (BRepBlend_SurfPointEvolRadInv::*)(const math_Vector &, math_Matrix &)) &BRepBlend_SurfPointEvolRadInv::Derivatives, "returns the values <D> of the derivatives for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("D"));
cls_BRepBlend_SurfPointEvolRadInv.def("Values", (Standard_Boolean (BRepBlend_SurfPointEvolRadInv::*)(const math_Vector &, math_Vector &, math_Matrix &)) &BRepBlend_SurfPointEvolRadInv::Values, "returns the values <F> of the functions and the derivatives <D> for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"), py::arg("D"));
cls_BRepBlend_SurfPointEvolRadInv.def("Set", (void (BRepBlend_SurfPointEvolRadInv::*)(const gp_Pnt &)) &BRepBlend_SurfPointEvolRadInv::Set, "Set the Point on which a solution has to be found.", py::arg("P"));
cls_BRepBlend_SurfPointEvolRadInv.def("GetTolerance", (void (BRepBlend_SurfPointEvolRadInv::*)(math_Vector &, const Standard_Real) const) &BRepBlend_SurfPointEvolRadInv::GetTolerance, "Returns in the vector Tolerance the parametric tolerance for each of the 3 variables; Tol is the tolerance used in 3d space.", py::arg("Tolerance"), py::arg("Tol"));
cls_BRepBlend_SurfPointEvolRadInv.def("GetBounds", (void (BRepBlend_SurfPointEvolRadInv::*)(math_Vector &, math_Vector &) const) &BRepBlend_SurfPointEvolRadInv::GetBounds, "Returns in the vector InfBound the lowest values allowed for each of the 3 variables. Returns in the vector SupBound the greatest values allowed for each of the 3 variables.", py::arg("InfBound"), py::arg("SupBound"));
cls_BRepBlend_SurfPointEvolRadInv.def("IsSolution", (Standard_Boolean (BRepBlend_SurfPointEvolRadInv::*)(const math_Vector &, const Standard_Real)) &BRepBlend_SurfPointEvolRadInv::IsSolution, "Returns Standard_True if Sol is a zero of the function. Tol is the tolerance used in 3d space.", py::arg("Sol"), py::arg("Tol"));

// Enums

}