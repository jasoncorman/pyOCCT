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
#include <Standard_TypeDef.hxx>
#include <TopoDS_Shape.hxx>
#include <StlAPI_Reader.hxx>

void bind_StlAPI_Reader(py::module &mod){

py::class_<StlAPI_Reader, std::unique_ptr<StlAPI_Reader, Deleter<StlAPI_Reader>>> cls_StlAPI_Reader(mod, "StlAPI_Reader", "Reading from stereolithography format.");

// Constructors

// Fields

// Methods
cls_StlAPI_Reader.def("Read", (Standard_Boolean (StlAPI_Reader::*)(TopoDS_Shape &, const Standard_CString)) &StlAPI_Reader::Read, "Reads STL file to the TopoDS_Shape (each triangle is converted to the face).", py::arg("theShape"), py::arg("theFileName"));

// Enums

}