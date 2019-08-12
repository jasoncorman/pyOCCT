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
#include <TopOpeBRepDS_GeometryData.hxx>
#include <Standard.hxx>
#include <TopOpeBRepDS_Curve.hxx>
#include <TopOpeBRepDS_DataStructure.hxx>
#include <TopOpeBRepDS_CurveData.hxx>

void bind_TopOpeBRepDS_CurveData(py::module &mod){

py::class_<TopOpeBRepDS_CurveData, std::unique_ptr<TopOpeBRepDS_CurveData, Deleter<TopOpeBRepDS_CurveData>>, TopOpeBRepDS_GeometryData> cls_TopOpeBRepDS_CurveData(mod, "TopOpeBRepDS_CurveData", "None");

// Constructors
cls_TopOpeBRepDS_CurveData.def(py::init<>());
cls_TopOpeBRepDS_CurveData.def(py::init<const TopOpeBRepDS_Curve &>(), py::arg("C"));

// Fields

// Methods
// cls_TopOpeBRepDS_CurveData.def_static("operator new_", (void * (*)(size_t)) &TopOpeBRepDS_CurveData::operator new, "None", py::arg("theSize"));
// cls_TopOpeBRepDS_CurveData.def_static("operator delete_", (void (*)(void *)) &TopOpeBRepDS_CurveData::operator delete, "None", py::arg("theAddress"));
// cls_TopOpeBRepDS_CurveData.def_static("operator new[]_", (void * (*)(size_t)) &TopOpeBRepDS_CurveData::operator new[], "None", py::arg("theSize"));
// cls_TopOpeBRepDS_CurveData.def_static("operator delete[]_", (void (*)(void *)) &TopOpeBRepDS_CurveData::operator delete[], "None", py::arg("theAddress"));
// cls_TopOpeBRepDS_CurveData.def_static("operator new_", (void * (*)(size_t, void *)) &TopOpeBRepDS_CurveData::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_TopOpeBRepDS_CurveData.def_static("operator delete_", (void (*)(void *, void *)) &TopOpeBRepDS_CurveData::operator delete, "None", py::arg(""), py::arg(""));

// Enums

}