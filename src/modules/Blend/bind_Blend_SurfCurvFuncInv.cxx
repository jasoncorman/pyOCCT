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
#include <math_FunctionSetWithDerivatives.hxx>
#include <Standard.hxx>
#include <Standard_TypeDef.hxx>
#include <math_Vector.hxx>
#include <math_Matrix.hxx>
#include <Standard_Handle.hxx>
#include <Adaptor2d_HCurve2d.hxx>
#include <Blend_SurfCurvFuncInv.hxx>

void bind_Blend_SurfCurvFuncInv(py::module &mod){

py::class_<Blend_SurfCurvFuncInv, std::unique_ptr<Blend_SurfCurvFuncInv, Deleter<Blend_SurfCurvFuncInv>>, math_FunctionSetWithDerivatives> cls_Blend_SurfCurvFuncInv(mod, "Blend_SurfCurvFuncInv", "Deferred class for a function used to compute a blending surface between a surface and a curve, using a guide line. This function is used to find a solution on a done restriction of the surface.");

// Fields

// Methods
// cls_Blend_SurfCurvFuncInv.def_static("operator new_", (void * (*)(size_t)) &Blend_SurfCurvFuncInv::operator new, "None", py::arg("theSize"));
// cls_Blend_SurfCurvFuncInv.def_static("operator delete_", (void (*)(void *)) &Blend_SurfCurvFuncInv::operator delete, "None", py::arg("theAddress"));
// cls_Blend_SurfCurvFuncInv.def_static("operator new[]_", (void * (*)(size_t)) &Blend_SurfCurvFuncInv::operator new[], "None", py::arg("theSize"));
// cls_Blend_SurfCurvFuncInv.def_static("operator delete[]_", (void (*)(void *)) &Blend_SurfCurvFuncInv::operator delete[], "None", py::arg("theAddress"));
// cls_Blend_SurfCurvFuncInv.def_static("operator new_", (void * (*)(size_t, void *)) &Blend_SurfCurvFuncInv::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_Blend_SurfCurvFuncInv.def_static("operator delete_", (void (*)(void *, void *)) &Blend_SurfCurvFuncInv::operator delete, "None", py::arg(""), py::arg(""));
cls_Blend_SurfCurvFuncInv.def("NbVariables", (Standard_Integer (Blend_SurfCurvFuncInv::*)() const) &Blend_SurfCurvFuncInv::NbVariables, "Returns 3.");
cls_Blend_SurfCurvFuncInv.def("NbEquations", (Standard_Integer (Blend_SurfCurvFuncInv::*)() const) &Blend_SurfCurvFuncInv::NbEquations, "returns the number of equations of the function.");
cls_Blend_SurfCurvFuncInv.def("Value", (Standard_Boolean (Blend_SurfCurvFuncInv::*)(const math_Vector &, math_Vector &)) &Blend_SurfCurvFuncInv::Value, "computes the values <F> of the Functions for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"));
cls_Blend_SurfCurvFuncInv.def("Derivatives", (Standard_Boolean (Blend_SurfCurvFuncInv::*)(const math_Vector &, math_Matrix &)) &Blend_SurfCurvFuncInv::Derivatives, "returns the values <D> of the derivatives for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("D"));
cls_Blend_SurfCurvFuncInv.def("Values", (Standard_Boolean (Blend_SurfCurvFuncInv::*)(const math_Vector &, math_Vector &, math_Matrix &)) &Blend_SurfCurvFuncInv::Values, "returns the values <F> of the functions and the derivatives <D> for the variable <X>. Returns True if the computation was done successfully, False otherwise.", py::arg("X"), py::arg("F"), py::arg("D"));
cls_Blend_SurfCurvFuncInv.def("Set", (void (Blend_SurfCurvFuncInv::*)(const opencascade::handle<Adaptor2d_HCurve2d> &)) &Blend_SurfCurvFuncInv::Set, "Set the Point on which a solution has to be found.", py::arg("Rst"));
cls_Blend_SurfCurvFuncInv.def("GetTolerance", (void (Blend_SurfCurvFuncInv::*)(math_Vector &, const Standard_Real) const) &Blend_SurfCurvFuncInv::GetTolerance, "Returns in the vector Tolerance the parametric tolerance for each of the 3 variables; Tol is the tolerance used in 3d space.", py::arg("Tolerance"), py::arg("Tol"));
cls_Blend_SurfCurvFuncInv.def("GetBounds", (void (Blend_SurfCurvFuncInv::*)(math_Vector &, math_Vector &) const) &Blend_SurfCurvFuncInv::GetBounds, "Returns in the vector InfBound the lowest values allowed for each of the 3 variables. Returns in the vector SupBound the greatest values allowed for each of the 3 variables.", py::arg("InfBound"), py::arg("SupBound"));
cls_Blend_SurfCurvFuncInv.def("IsSolution", (Standard_Boolean (Blend_SurfCurvFuncInv::*)(const math_Vector &, const Standard_Real)) &Blend_SurfCurvFuncInv::IsSolution, "Returns Standard_True if Sol is a zero of the function. Tol is the tolerance used in 3d space.", py::arg("Sol"), py::arg("Tol"));

// Enums

}