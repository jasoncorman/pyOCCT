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
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>
#include <ShapeExtend_WireData.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Vertex.hxx>
#include <ShapeAnalysis_Geom.hxx>
#include <ShapeAnalysis_Curve.hxx>
#include <ShapeAnalysis_Surface.hxx>
#include <ShapeAnalysis_Edge.hxx>
#include <ShapeAnalysis_Wire.hxx>
#include <ShapeAnalysis_WireOrder.hxx>
#include <ShapeAnalysis_WireVertex.hxx>
#include <ShapeAnalysis_CheckSmallFace.hxx>
#include <ShapeAnalysis_Shell.hxx>
#include <ShapeAnalysis_ShapeTolerance.hxx>
#include <ShapeAnalysis_ShapeContents.hxx>
#include <ShapeAnalysis_FreeBounds.hxx>
#include <ShapeAnalysis_FreeBoundData.hxx>
#include <ShapeAnalysis_FreeBoundsProperties.hxx>
#include <ShapeAnalysis_TransferParameters.hxx>
#include <ShapeAnalysis_TransferParametersProj.hxx>
#include <ShapeAnalysis.hxx>
#include <NCollection_UBTree.hxx>
#include <Bnd_Box.hxx>
#include <ShapeAnalysis_BoxBndTree.hxx>
#include <TopTools_HArray1OfShape.hxx>
#include <ShapeExtend.hxx>
#include <gp_Pnt.hxx>
#include <ShapeExtend_Status.hxx>
#include <TColStd_MapOfInteger.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <NCollection_DataMap.hxx>
#include <TColStd_ListOfReal.hxx>
#include <TopTools_ShapeMapHasher.hxx>
#include <ShapeAnalysis_DataMapOfShapeListOfReal.hxx>
#include <TopoDS_Edge.hxx>
#include <TopTools_DataMapOfShapeListOfShape.hxx>
#include <TopoDS_Compound.hxx>
#include <TopTools_DataMapOfShapeShape.hxx>
#include <Geom_Curve.hxx>
#include <Adaptor3d_Curve.hxx>
#include <Geom2d_Curve.hxx>
#include <Bnd_Box2d.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <gp_XYZ.hxx>
#include <TColgp_SequenceOfPnt2d.hxx>
#include <TColgp_SequenceOfPnt.hxx>
#include <Geom_Surface.hxx>
#include <TopLoc_Location.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Vec2d.hxx>
#include <Standard_Transient.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <Standard_Type.hxx>
#include <TopTools_DataMapOfShapeReal.hxx>
#include <NCollection_Sequence.hxx>
#include <ShapeAnalysis_SequenceOfFreeBounds.hxx>
#include <NCollection_BaseAllocator.hxx>
#include <ShapeAnalysis_HSequenceOfFreeBounds.hxx>
#include <gp_Pln.hxx>
#include <TColStd_HArray2OfReal.hxx>
#include <gp_Trsf.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <GeomAdaptor_HSurface.hxx>
#include <Extrema_ExtPS.hxx>
#include <TColStd_HSequenceOfReal.hxx>
#include <Adaptor3d_CurveOnSurface.hxx>
#include <IntRes2d_SequenceOfIntersectionPoint.hxx>
#include <TColStd_SequenceOfReal.hxx>
#include <TopTools_MapOfShape.hxx>
#include <gp_XY.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <TColgp_HSequenceOfXYZ.hxx>
#include <TColgp_HArray1OfXYZ.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <bind_NCollection_UBTree.hxx>
#include <bind_NCollection_DataMap.hxx>
#include <bind_NCollection_Sequence.hxx>

PYBIND11_MODULE(ShapeAnalysis, mod) {

py::module::import("OCCT.Standard");
py::module::import("OCCT.TopoDS");
py::module::import("OCCT.ShapeExtend");
py::module::import("OCCT.NCollection");
py::module::import("OCCT.Bnd");
py::module::import("OCCT.TopTools");
py::module::import("OCCT.gp");
py::module::import("OCCT.TColStd");
py::module::import("OCCT.Geom");
py::module::import("OCCT.Adaptor3d");
py::module::import("OCCT.Geom2d");
py::module::import("OCCT.TColgp");
py::module::import("OCCT.TopLoc");
py::module::import("OCCT.TopAbs");
py::module::import("OCCT.GeomAdaptor");
py::module::import("OCCT.Extrema");
py::module::import("OCCT.IntRes2d");

// CLASS: SHAPEANALYSIS
py::class_<ShapeAnalysis> cls_ShapeAnalysis(mod, "ShapeAnalysis", "This package is intended to analyze geometrical objects and topological shapes. Analysis domain includes both exploring geometrical and topological properties of shapes and checking their conformance to Open CASCADE requirements. The directions of analysis provided by tools of this package are: computing quantities of subshapes, computing parameters of points on curve and surface, computing surface singularities, checking edge and wire consistency, checking edges order in the wire, checking face bounds orientation, checking small faces, analyzing shape tolerances, analyzing of free bounds of the shape.");

// Methods
// cls_ShapeAnalysis.def_static("operator new_", (void * (*)(size_t)) &ShapeAnalysis::operator new, "None", py::arg("theSize"));
// cls_ShapeAnalysis.def_static("operator delete_", (void (*)(void *)) &ShapeAnalysis::operator delete, "None", py::arg("theAddress"));
// cls_ShapeAnalysis.def_static("operator new[]_", (void * (*)(size_t)) &ShapeAnalysis::operator new[], "None", py::arg("theSize"));
// cls_ShapeAnalysis.def_static("operator delete[]_", (void (*)(void *)) &ShapeAnalysis::operator delete[], "None", py::arg("theAddress"));
// cls_ShapeAnalysis.def_static("operator new_", (void * (*)(size_t, void *)) &ShapeAnalysis::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ShapeAnalysis.def_static("operator delete_", (void (*)(void *, void *)) &ShapeAnalysis::operator delete, "None", py::arg(""), py::arg(""));
cls_ShapeAnalysis.def_static("OuterWire_", (TopoDS_Wire (*)(const TopoDS_Face &)) &ShapeAnalysis::OuterWire, "Returns the outer wire on the face <Face>. This is replacement of the method BRepTools::OuterWire until it works badly. Returns the first wire oriented as outer according to FClass2d_Classifier. If none, last wire is returned.", py::arg("face"));
cls_ShapeAnalysis.def_static("TotCross2D_", (Standard_Real (*)(const opencascade::handle<ShapeExtend_WireData> &, const TopoDS_Face &)) &ShapeAnalysis::TotCross2D, "Returns a total area of 2d wire", py::arg("sewd"), py::arg("aFace"));
cls_ShapeAnalysis.def_static("ContourArea_", (Standard_Real (*)(const TopoDS_Wire &)) &ShapeAnalysis::ContourArea, "Returns a total area of 3d wire", py::arg("theWire"));
cls_ShapeAnalysis.def_static("IsOuterBound_", (Standard_Boolean (*)(const TopoDS_Face &)) &ShapeAnalysis::IsOuterBound, "Returns True if <F> has outer bound.", py::arg("face"));
cls_ShapeAnalysis.def_static("AdjustByPeriod_", (Standard_Real (*)(const Standard_Real, const Standard_Real, const Standard_Real)) &ShapeAnalysis::AdjustByPeriod, "Returns a shift required to move point <Val> to the range [ToVal-Period/2,ToVal+Period/2]. This shift will be the divisible by Period. Intended for adjusting parameters on periodic surfaces.", py::arg("Val"), py::arg("ToVal"), py::arg("Period"));
cls_ShapeAnalysis.def_static("AdjustToPeriod_", (Standard_Real (*)(const Standard_Real, const Standard_Real, const Standard_Real)) &ShapeAnalysis::AdjustToPeriod, "Returns a shift required to move point <Val> to the range [ValMin,ValMax]. This shift will be the divisible by Period with Period = ValMax - ValMin. Intended for adjusting parameters on periodic surfaces.", py::arg("Val"), py::arg("ValMin"), py::arg("ValMax"));
cls_ShapeAnalysis.def_static("FindBounds_", (void (*)(const TopoDS_Shape &, TopoDS_Vertex &, TopoDS_Vertex &)) &ShapeAnalysis::FindBounds, "Finds the start and end vertices of the shape Shape can be of the following type: vertex: V1 and V2 are the same and equal to <shape>, edge : V1 is start and V2 is end vertex (see ShapeAnalysis_Edge methods FirstVertex and LastVertex), wire : V1 is start vertex of the first edge, V2 is end vertex of the last edge (also see ShapeAnalysis_Edge). If wire contains no edges V1 and V2 are nullified If none of the above V1 and V2 are nullified", py::arg("shape"), py::arg("V1"), py::arg("V2"));
cls_ShapeAnalysis.def_static("GetFaceUVBounds_", [](const TopoDS_Face & F, Standard_Real & Umin, Standard_Real & Umax, Standard_Real & Vmin, Standard_Real & Vmax){ ShapeAnalysis::GetFaceUVBounds(F, Umin, Umax, Vmin, Vmax); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &>(Umin, Umax, Vmin, Vmax); }, "Computes exact UV bounds of all wires on the face", py::arg("F"), py::arg("Umin"), py::arg("Umax"), py::arg("Vmin"), py::arg("Vmax"));

// TYPEDEF: SHAPEANALYSIS_BOXBNDTREE
bind_NCollection_UBTree<int, Bnd_Box>(mod, "ShapeAnalysis_BoxBndTree", py::module_local());

// CLASS: SHAPEANALYSIS_BOXBNDTREESELECTOR
py::class_<ShapeAnalysis_BoxBndTreeSelector, ShapeAnalysis_BoxBndTree::Selector> cls_ShapeAnalysis_BoxBndTreeSelector(mod, "ShapeAnalysis_BoxBndTreeSelector", "None");

// Constructors
// cls_ShapeAnalysis_BoxBndTreeSelector.def(py::init<opencascade::handle<TopTools_HArray1OfShape>, Standard_Boolean>(), py::arg("theSeq"), py::arg("theShared"));

// Methods
cls_ShapeAnalysis_BoxBndTreeSelector.def("DefineBoxes", (void (ShapeAnalysis_BoxBndTreeSelector::*)(const Bnd_Box &, const Bnd_Box &)) &ShapeAnalysis_BoxBndTreeSelector::DefineBoxes, "None", py::arg("theFBox"), py::arg("theLBox"));
cls_ShapeAnalysis_BoxBndTreeSelector.def("DefineVertexes", (void (ShapeAnalysis_BoxBndTreeSelector::*)(TopoDS_Vertex, TopoDS_Vertex)) &ShapeAnalysis_BoxBndTreeSelector::DefineVertexes, "None", py::arg("theVf"), py::arg("theVl"));
cls_ShapeAnalysis_BoxBndTreeSelector.def("DefinePnt", (void (ShapeAnalysis_BoxBndTreeSelector::*)(gp_Pnt, gp_Pnt)) &ShapeAnalysis_BoxBndTreeSelector::DefinePnt, "None", py::arg("theFPnt"), py::arg("theLPnt"));
cls_ShapeAnalysis_BoxBndTreeSelector.def("GetNb", (Standard_Integer (ShapeAnalysis_BoxBndTreeSelector::*)()) &ShapeAnalysis_BoxBndTreeSelector::GetNb, "None");
cls_ShapeAnalysis_BoxBndTreeSelector.def("SetNb", (void (ShapeAnalysis_BoxBndTreeSelector::*)(Standard_Integer)) &ShapeAnalysis_BoxBndTreeSelector::SetNb, "None", py::arg("theNb"));
cls_ShapeAnalysis_BoxBndTreeSelector.def("LoadList", (void (ShapeAnalysis_BoxBndTreeSelector::*)(Standard_Integer)) &ShapeAnalysis_BoxBndTreeSelector::LoadList, "None", py::arg("elem"));
cls_ShapeAnalysis_BoxBndTreeSelector.def("SetStop", (void (ShapeAnalysis_BoxBndTreeSelector::*)()) &ShapeAnalysis_BoxBndTreeSelector::SetStop, "None");
cls_ShapeAnalysis_BoxBndTreeSelector.def("SetTolerance", (void (ShapeAnalysis_BoxBndTreeSelector::*)(Standard_Real)) &ShapeAnalysis_BoxBndTreeSelector::SetTolerance, "None", py::arg("theTol"));
cls_ShapeAnalysis_BoxBndTreeSelector.def("ContWire", (Standard_Boolean (ShapeAnalysis_BoxBndTreeSelector::*)(Standard_Integer)) &ShapeAnalysis_BoxBndTreeSelector::ContWire, "None", py::arg("nbWire"));
cls_ShapeAnalysis_BoxBndTreeSelector.def("LastCheckStatus", (Standard_Boolean (ShapeAnalysis_BoxBndTreeSelector::*)(const ShapeExtend_Status) const) &ShapeAnalysis_BoxBndTreeSelector::LastCheckStatus, "None", py::arg("theStatus"));
cls_ShapeAnalysis_BoxBndTreeSelector.def("Reject", (Standard_Boolean (ShapeAnalysis_BoxBndTreeSelector::*)(const Bnd_Box &) const) &ShapeAnalysis_BoxBndTreeSelector::Reject, "None", py::arg("theBnd"));
cls_ShapeAnalysis_BoxBndTreeSelector.def("Accept", (Standard_Boolean (ShapeAnalysis_BoxBndTreeSelector::*)(const Standard_Integer &)) &ShapeAnalysis_BoxBndTreeSelector::Accept, "None", py::arg(""));

// TYPEDEF: SHAPEANALYSIS_DATAMAPOFSHAPELISTOFREAL
bind_NCollection_DataMap<TopoDS_Shape, NCollection_List<double>, TopTools_ShapeMapHasher>(mod, "ShapeAnalysis_DataMapOfShapeListOfReal", py::module_local(false));

// TYPEDEF: SHAPEANALYSIS_DATAMAPITERATOROFDATAMAPOFSHAPELISTOFREAL

// CLASS: SHAPEANALYSIS_CHECKSMALLFACE
py::class_<ShapeAnalysis_CheckSmallFace> cls_ShapeAnalysis_CheckSmallFace(mod, "ShapeAnalysis_CheckSmallFace", "Analysis of the face size");

// Constructors
cls_ShapeAnalysis_CheckSmallFace.def(py::init<>());

// Methods
// cls_ShapeAnalysis_CheckSmallFace.def_static("operator new_", (void * (*)(size_t)) &ShapeAnalysis_CheckSmallFace::operator new, "None", py::arg("theSize"));
// cls_ShapeAnalysis_CheckSmallFace.def_static("operator delete_", (void (*)(void *)) &ShapeAnalysis_CheckSmallFace::operator delete, "None", py::arg("theAddress"));
// cls_ShapeAnalysis_CheckSmallFace.def_static("operator new[]_", (void * (*)(size_t)) &ShapeAnalysis_CheckSmallFace::operator new[], "None", py::arg("theSize"));
// cls_ShapeAnalysis_CheckSmallFace.def_static("operator delete[]_", (void (*)(void *)) &ShapeAnalysis_CheckSmallFace::operator delete[], "None", py::arg("theAddress"));
// cls_ShapeAnalysis_CheckSmallFace.def_static("operator new_", (void * (*)(size_t, void *)) &ShapeAnalysis_CheckSmallFace::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ShapeAnalysis_CheckSmallFace.def_static("operator delete_", (void (*)(void *, void *)) &ShapeAnalysis_CheckSmallFace::operator delete, "None", py::arg(""), py::arg(""));
cls_ShapeAnalysis_CheckSmallFace.def("IsSpotFace", [](ShapeAnalysis_CheckSmallFace &self, const TopoDS_Face & F, gp_Pnt & spot, Standard_Real & spotol, const Standard_Real tol){ Standard_Integer rv = self.IsSpotFace(F, spot, spotol, tol); return std::tuple<Standard_Integer, Standard_Real &>(rv, spotol); }, "Checks if a Face is as a Spot Returns 0 if not, 1 if yes, 2 if yes and all vertices are the same By default, considers the tolerance zone of its vertices A given value <tol> may be given to check a spot of this size If a Face is a Spot, its location is returned in <spot>, and <spotol> returns an equivalent tolerance, which is computed as half of max dimension of min-max box of the face", py::arg("F"), py::arg("spot"), py::arg("spotol"), py::arg("tol"));
cls_ShapeAnalysis_CheckSmallFace.def("CheckSpotFace", [](ShapeAnalysis_CheckSmallFace &self, const TopoDS_Face & a0) -> Standard_Boolean { return self.CheckSpotFace(a0); });
cls_ShapeAnalysis_CheckSmallFace.def("CheckSpotFace", (Standard_Boolean (ShapeAnalysis_CheckSmallFace::*)(const TopoDS_Face &, const Standard_Real)) &ShapeAnalysis_CheckSmallFace::CheckSpotFace, "Acts as IsSpotFace, but records in <infos> a diagnostic 'SpotFace' with the Pnt as value (data 'Location')", py::arg("F"), py::arg("tol"));
cls_ShapeAnalysis_CheckSmallFace.def("IsStripSupport", [](ShapeAnalysis_CheckSmallFace &self, const TopoDS_Face & a0) -> Standard_Boolean { return self.IsStripSupport(a0); });
cls_ShapeAnalysis_CheckSmallFace.def("IsStripSupport", (Standard_Boolean (ShapeAnalysis_CheckSmallFace::*)(const TopoDS_Face &, const Standard_Real)) &ShapeAnalysis_CheckSmallFace::IsStripSupport, "Checks if a Face lies on a Surface which is a strip So the Face is a strip. But a Face may be a strip elsewhere ..", py::arg("F"), py::arg("tol"));
cls_ShapeAnalysis_CheckSmallFace.def("CheckStripEdges", [](ShapeAnalysis_CheckSmallFace &self, const TopoDS_Edge & E1, const TopoDS_Edge & E2, const Standard_Real tol, Standard_Real & dmax){ Standard_Boolean rv = self.CheckStripEdges(E1, E2, tol, dmax); return std::tuple<Standard_Boolean, Standard_Real &>(rv, dmax); }, "Checks if two edges define a strip, i.e. distance maxi below tolerance, given or some of those of E1 and E2", py::arg("E1"), py::arg("E2"), py::arg("tol"), py::arg("dmax"));
cls_ShapeAnalysis_CheckSmallFace.def("FindStripEdges", [](ShapeAnalysis_CheckSmallFace &self, const TopoDS_Face & F, TopoDS_Edge & E1, TopoDS_Edge & E2, const Standard_Real tol, Standard_Real & dmax){ Standard_Boolean rv = self.FindStripEdges(F, E1, E2, tol, dmax); return std::tuple<Standard_Boolean, Standard_Real &>(rv, dmax); }, "Searchs for two and only two edges up tolerance Returns True if OK, false if not 2 edges If True, returns the two edges and their maximum distance", py::arg("F"), py::arg("E1"), py::arg("E2"), py::arg("tol"), py::arg("dmax"));
cls_ShapeAnalysis_CheckSmallFace.def("CheckSingleStrip", [](ShapeAnalysis_CheckSmallFace &self, const TopoDS_Face & a0, TopoDS_Edge & a1, TopoDS_Edge & a2) -> Standard_Boolean { return self.CheckSingleStrip(a0, a1, a2); });
cls_ShapeAnalysis_CheckSmallFace.def("CheckSingleStrip", (Standard_Boolean (ShapeAnalysis_CheckSmallFace::*)(const TopoDS_Face &, TopoDS_Edge &, TopoDS_Edge &, const Standard_Real)) &ShapeAnalysis_CheckSmallFace::CheckSingleStrip, "Checks if a Face is a single strip, i.e. brings two great edges which are confused on their whole length, possible other edges are small or null length", py::arg("F"), py::arg("E1"), py::arg("E2"), py::arg("tol"));
cls_ShapeAnalysis_CheckSmallFace.def("CheckStripFace", [](ShapeAnalysis_CheckSmallFace &self, const TopoDS_Face & a0, TopoDS_Edge & a1, TopoDS_Edge & a2) -> Standard_Boolean { return self.CheckStripFace(a0, a1, a2); });
cls_ShapeAnalysis_CheckSmallFace.def("CheckStripFace", (Standard_Boolean (ShapeAnalysis_CheckSmallFace::*)(const TopoDS_Face &, TopoDS_Edge &, TopoDS_Edge &, const Standard_Real)) &ShapeAnalysis_CheckSmallFace::CheckStripFace, "Checks if a Face is as a Strip Returns 0 if not or non determined, 1 if in U, 2 if in V By default, considers the tolerance zone of its edges A given value <tol> may be given to check a strip of max this width", py::arg("F"), py::arg("E1"), py::arg("E2"), py::arg("tol"));
cls_ShapeAnalysis_CheckSmallFace.def("CheckSplittingVertices", (Standard_Integer (ShapeAnalysis_CheckSmallFace::*)(const TopoDS_Face &, TopTools_DataMapOfShapeListOfShape &, ShapeAnalysis_DataMapOfShapeListOfReal &, TopoDS_Compound &)) &ShapeAnalysis_CheckSmallFace::CheckSplittingVertices, "Checks if a Face brings vertices which split it, either confused with non adjacent vertices, or confused with their projection on non adjacent edges Returns the count of found splitting vertices Each vertex then brings a diagnostic 'SplittingVertex', with data : 'Face' for the face, 'Edge' for the split edge", py::arg("F"), py::arg("MapEdges"), py::arg("MapParam"), py::arg("theAllVert"));
cls_ShapeAnalysis_CheckSmallFace.def("CheckPin", [](ShapeAnalysis_CheckSmallFace &self, const TopoDS_Face & F, Standard_Integer & whatrow, Standard_Integer & sence){ Standard_Boolean rv = self.CheckPin(F, whatrow, sence); return std::tuple<Standard_Boolean, Standard_Integer &, Standard_Integer &>(rv, whatrow, sence); }, "Checks if a Face has a pin, which can be edited No singularity : no pin, returns 0 If there is a pin, checked topics, with returned value : - 0 : nothing to do more - 1 : 'smooth', i.e. not a really sharp pin -> diagnostic 'SmoothPin' - 2 : stretched pin, i.e. is possible to relimit the face by another vertex, so that this vertex still gives a pin -> diagnostic 'StretchedPin' with location of vertex (Pnt)", py::arg("F"), py::arg("whatrow"), py::arg("sence"));
cls_ShapeAnalysis_CheckSmallFace.def("CheckTwisted", [](ShapeAnalysis_CheckSmallFace &self, const TopoDS_Face & F, Standard_Real & paramu, Standard_Real & paramv){ Standard_Boolean rv = self.CheckTwisted(F, paramu, paramv); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &>(rv, paramu, paramv); }, "Checks if a Face is twisted (apart from checking Pin, i.e. it does not give information on pin, only 'it is twisted')", py::arg("F"), py::arg("paramu"), py::arg("paramv"));
cls_ShapeAnalysis_CheckSmallFace.def("CheckPinFace", [](ShapeAnalysis_CheckSmallFace &self, const TopoDS_Face & a0, TopTools_DataMapOfShapeShape & a1) -> Standard_Boolean { return self.CheckPinFace(a0, a1); });
cls_ShapeAnalysis_CheckSmallFace.def("CheckPinFace", (Standard_Boolean (ShapeAnalysis_CheckSmallFace::*)(const TopoDS_Face &, TopTools_DataMapOfShapeShape &, const Standard_Real)) &ShapeAnalysis_CheckSmallFace::CheckPinFace, "None", py::arg("F"), py::arg("mapEdges"), py::arg("toler"));
cls_ShapeAnalysis_CheckSmallFace.def("CheckPinEdges", (Standard_Boolean (ShapeAnalysis_CheckSmallFace::*)(const TopoDS_Edge &, const TopoDS_Edge &, const Standard_Real, const Standard_Real, const Standard_Real) const) &ShapeAnalysis_CheckSmallFace::CheckPinEdges, "None", py::arg("theFirstEdge"), py::arg("theSecondEdge"), py::arg("coef1"), py::arg("coef2"), py::arg("toler"));
cls_ShapeAnalysis_CheckSmallFace.def("Status", (Standard_Boolean (ShapeAnalysis_CheckSmallFace::*)(const ShapeExtend_Status) const) &ShapeAnalysis_CheckSmallFace::Status, "Returns the status of last call to Perform() ShapeExtend_OK : face was OK, nothing done ShapeExtend_DONE1: some wires are fixed ShapeExtend_DONE2: orientation of wires fixed ShapeExtend_DONE3: missing seam added ShapeExtend_DONE4: small area wire removed ShapeExtend_DONE5: natural bounds added ShapeExtend_FAIL1: some fails during fixing wires ShapeExtend_FAIL2: cannot fix orientation of wires ShapeExtend_FAIL3: cannot add missing seam ShapeExtend_FAIL4: cannot remove small area wire", py::arg("status"));
cls_ShapeAnalysis_CheckSmallFace.def("SetTolerance", (void (ShapeAnalysis_CheckSmallFace::*)(const Standard_Real)) &ShapeAnalysis_CheckSmallFace::SetTolerance, "Sets a fixed Tolerance to check small face By default, local tolerance zone is considered Sets a fixed MaxTolerance to check small face Sets a fixed Tolerance to check small face By default, local tolerance zone is considered Unset fixed tolerance, comes back to local tolerance zones Unset fixed tolerance, comes back to local tolerance zones", py::arg("tol"));
cls_ShapeAnalysis_CheckSmallFace.def("Tolerance", (Standard_Real (ShapeAnalysis_CheckSmallFace::*)() const) &ShapeAnalysis_CheckSmallFace::Tolerance, "Returns the tolerance to check small faces, negative value if local tolerances zones are to be considered");
cls_ShapeAnalysis_CheckSmallFace.def("StatusSpot", (Standard_Boolean (ShapeAnalysis_CheckSmallFace::*)(const ShapeExtend_Status) const) &ShapeAnalysis_CheckSmallFace::StatusSpot, "None", py::arg("status"));
cls_ShapeAnalysis_CheckSmallFace.def("StatusStrip", (Standard_Boolean (ShapeAnalysis_CheckSmallFace::*)(const ShapeExtend_Status) const) &ShapeAnalysis_CheckSmallFace::StatusStrip, "None", py::arg("status"));
cls_ShapeAnalysis_CheckSmallFace.def("StatusPin", (Standard_Boolean (ShapeAnalysis_CheckSmallFace::*)(const ShapeExtend_Status) const) &ShapeAnalysis_CheckSmallFace::StatusPin, "None", py::arg("status"));
cls_ShapeAnalysis_CheckSmallFace.def("StatusTwisted", (Standard_Boolean (ShapeAnalysis_CheckSmallFace::*)(const ShapeExtend_Status) const) &ShapeAnalysis_CheckSmallFace::StatusTwisted, "None", py::arg("status"));
cls_ShapeAnalysis_CheckSmallFace.def("StatusSplitVert", (Standard_Boolean (ShapeAnalysis_CheckSmallFace::*)(const ShapeExtend_Status) const) &ShapeAnalysis_CheckSmallFace::StatusSplitVert, "None", py::arg("status"));
cls_ShapeAnalysis_CheckSmallFace.def("StatusPinFace", (Standard_Boolean (ShapeAnalysis_CheckSmallFace::*)(const ShapeExtend_Status) const) &ShapeAnalysis_CheckSmallFace::StatusPinFace, "None", py::arg("status"));
cls_ShapeAnalysis_CheckSmallFace.def("StatusPinEdges", (Standard_Boolean (ShapeAnalysis_CheckSmallFace::*)(const ShapeExtend_Status) const) &ShapeAnalysis_CheckSmallFace::StatusPinEdges, "None", py::arg("status"));

// CLASS: SHAPEANALYSIS_CURVE
py::class_<ShapeAnalysis_Curve> cls_ShapeAnalysis_Curve(mod, "ShapeAnalysis_Curve", "Analyzing tool for 2d or 3d curve. Computes parameters of projected point onto a curve.");

// Methods
// cls_ShapeAnalysis_Curve.def_static("operator new_", (void * (*)(size_t)) &ShapeAnalysis_Curve::operator new, "None", py::arg("theSize"));
// cls_ShapeAnalysis_Curve.def_static("operator delete_", (void (*)(void *)) &ShapeAnalysis_Curve::operator delete, "None", py::arg("theAddress"));
// cls_ShapeAnalysis_Curve.def_static("operator new[]_", (void * (*)(size_t)) &ShapeAnalysis_Curve::operator new[], "None", py::arg("theSize"));
// cls_ShapeAnalysis_Curve.def_static("operator delete[]_", (void (*)(void *)) &ShapeAnalysis_Curve::operator delete[], "None", py::arg("theAddress"));
// cls_ShapeAnalysis_Curve.def_static("operator new_", (void * (*)(size_t, void *)) &ShapeAnalysis_Curve::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ShapeAnalysis_Curve.def_static("operator delete_", (void (*)(void *, void *)) &ShapeAnalysis_Curve::operator delete, "None", py::arg(""), py::arg(""));
cls_ShapeAnalysis_Curve.def("Project", [](ShapeAnalysis_Curve &self, const opencascade::handle<Geom_Curve> & C3D, const gp_Pnt & P3D, const Standard_Real preci, gp_Pnt & proj, Standard_Real & param, const Standard_Boolean AdjustToEnds){ Standard_Real rv = self.Project(C3D, P3D, preci, proj, param, AdjustToEnds); return std::tuple<Standard_Real, Standard_Real &>(rv, param); }, "Projects a Point on a Curve. Computes the projected point and its parameter on the curve. <preci> is used as 3d precision (hence, 0 will produce reject unless exact confusion). The number of iterations is limited. If AdjustToEnds is True, point will be adjusted to the end of the curve if distance is less than <preci>", py::arg("C3D"), py::arg("P3D"), py::arg("preci"), py::arg("proj"), py::arg("param"), py::arg("AdjustToEnds"));
cls_ShapeAnalysis_Curve.def("Project", [](ShapeAnalysis_Curve &self, const Adaptor3d_Curve & C3D, const gp_Pnt & P3D, const Standard_Real preci, gp_Pnt & proj, Standard_Real & param, const Standard_Boolean AdjustToEnds){ Standard_Real rv = self.Project(C3D, P3D, preci, proj, param, AdjustToEnds); return std::tuple<Standard_Real, Standard_Real &>(rv, param); }, "Projects a Point on a Curve. Computes the projected point and its parameter on the curve. <preci> is used as 3d precision (hence, 0 will produce reject unless exact confusion). The number of iterations is limited.", py::arg("C3D"), py::arg("P3D"), py::arg("preci"), py::arg("proj"), py::arg("param"), py::arg("AdjustToEnds"));
cls_ShapeAnalysis_Curve.def("Project", [](ShapeAnalysis_Curve &self, const opencascade::handle<Geom_Curve> & C3D, const gp_Pnt & P3D, const Standard_Real preci, gp_Pnt & proj, Standard_Real & param, const Standard_Real cf, const Standard_Real cl, const Standard_Boolean AdjustToEnds){ Standard_Real rv = self.Project(C3D, P3D, preci, proj, param, cf, cl, AdjustToEnds); return std::tuple<Standard_Real, Standard_Real &>(rv, param); }, "Projects a Point on a Curve, but parameters are limited between <cf> and <cl>. The range [cf, cl] is extended with help of Adaptor3d on the basis of 3d precision <preci>. If AdjustToEnds is True, point will be adjusted to the end of the curve if distance is less than <preci>", py::arg("C3D"), py::arg("P3D"), py::arg("preci"), py::arg("proj"), py::arg("param"), py::arg("cf"), py::arg("cl"), py::arg("AdjustToEnds"));
cls_ShapeAnalysis_Curve.def("ProjectAct", [](ShapeAnalysis_Curve &self, const Adaptor3d_Curve & C3D, const gp_Pnt & P3D, const Standard_Real preci, gp_Pnt & proj, Standard_Real & param){ Standard_Real rv = self.ProjectAct(C3D, P3D, preci, proj, param); return std::tuple<Standard_Real, Standard_Real &>(rv, param); }, "None", py::arg("C3D"), py::arg("P3D"), py::arg("preci"), py::arg("proj"), py::arg("param"));
cls_ShapeAnalysis_Curve.def("NextProject", [](ShapeAnalysis_Curve &self, const Standard_Real paramPrev, const opencascade::handle<Geom_Curve> & C3D, const gp_Pnt & P3D, const Standard_Real preci, gp_Pnt & proj, Standard_Real & param, const Standard_Real cf, const Standard_Real cl, const Standard_Boolean AdjustToEnds){ Standard_Real rv = self.NextProject(paramPrev, C3D, P3D, preci, proj, param, cf, cl, AdjustToEnds); return std::tuple<Standard_Real, Standard_Real &>(rv, param); }, "Projects a Point on a Curve using Newton method. <paramPrev> is taken as the first approximation of solution. If Newton algorithm fails the method Project() is used. If AdjustToEnds is True, point will be adjusted to the end of the curve if distance is less than <preci>", py::arg("paramPrev"), py::arg("C3D"), py::arg("P3D"), py::arg("preci"), py::arg("proj"), py::arg("param"), py::arg("cf"), py::arg("cl"), py::arg("AdjustToEnds"));
cls_ShapeAnalysis_Curve.def("NextProject", [](ShapeAnalysis_Curve &self, const Standard_Real paramPrev, const Adaptor3d_Curve & C3D, const gp_Pnt & P3D, const Standard_Real preci, gp_Pnt & proj, Standard_Real & param){ Standard_Real rv = self.NextProject(paramPrev, C3D, P3D, preci, proj, param); return std::tuple<Standard_Real, Standard_Real &>(rv, param); }, "Projects a Point on a Curve using Newton method. <paramPrev> is taken as the first approximation of solution. If Newton algorithm fails the method Project() is used.", py::arg("paramPrev"), py::arg("C3D"), py::arg("P3D"), py::arg("preci"), py::arg("proj"), py::arg("param"));
cls_ShapeAnalysis_Curve.def("ValidateRange", [](ShapeAnalysis_Curve &self, const opencascade::handle<Geom_Curve> & Crv, Standard_Real & First, Standard_Real & Last, const Standard_Real prec){ Standard_Boolean rv = self.ValidateRange(Crv, First, Last, prec); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &>(rv, First, Last); }, "Validate parameters First and Last for the given curve in order to make them valid for creation of edge. This includes: - limiting range [First,Last] by range of curve - adjusting range [First,Last] for periodic (or closed) curve if Last < First Returns True if parameters are OK or are successfully corrected, or False if parameters cannot be corrected. In the latter case, parameters are reset to range of curve.", py::arg("Crv"), py::arg("First"), py::arg("Last"), py::arg("prec"));
cls_ShapeAnalysis_Curve.def("FillBndBox", (void (ShapeAnalysis_Curve::*)(const opencascade::handle<Geom2d_Curve> &, const Standard_Real, const Standard_Real, const Standard_Integer, const Standard_Boolean, Bnd_Box2d &) const) &ShapeAnalysis_Curve::FillBndBox, "Computes a boundary box on segment of curve C2d from First to Last. This is done by taking NPoints points from the curve and, if Exact is True, by searching for exact extrema. All these points are added to Box.", py::arg("C2d"), py::arg("First"), py::arg("Last"), py::arg("NPoints"), py::arg("Exact"), py::arg("Box"));
cls_ShapeAnalysis_Curve.def("SelectForwardSeam", (Standard_Integer (ShapeAnalysis_Curve::*)(const opencascade::handle<Geom2d_Curve> &, const opencascade::handle<Geom2d_Curve> &) const) &ShapeAnalysis_Curve::SelectForwardSeam, "Defines which pcurve (C1 or C2) should be chosen for FORWARD seam edge.", py::arg("C1"), py::arg("C2"));
cls_ShapeAnalysis_Curve.def_static("IsPlanar_", [](const TColgp_Array1OfPnt & a0, gp_XYZ & a1) -> Standard_Boolean { return ShapeAnalysis_Curve::IsPlanar(a0, a1); });
cls_ShapeAnalysis_Curve.def_static("IsPlanar_", (Standard_Boolean (*)(const TColgp_Array1OfPnt &, gp_XYZ &, const Standard_Real)) &ShapeAnalysis_Curve::IsPlanar, "Checks if points are planar with given preci. If Normal has not zero modulus, checks with given normal", py::arg("pnts"), py::arg("Normal"), py::arg("preci"));
cls_ShapeAnalysis_Curve.def_static("IsPlanar_", [](const opencascade::handle<Geom_Curve> & a0, gp_XYZ & a1) -> Standard_Boolean { return ShapeAnalysis_Curve::IsPlanar(a0, a1); });
cls_ShapeAnalysis_Curve.def_static("IsPlanar_", (Standard_Boolean (*)(const opencascade::handle<Geom_Curve> &, gp_XYZ &, const Standard_Real)) &ShapeAnalysis_Curve::IsPlanar, "Checks if curve is planar with given preci. If Normal has not zero modulus, checks with given normal", py::arg("curve"), py::arg("Normal"), py::arg("preci"));
cls_ShapeAnalysis_Curve.def_static("GetSamplePoints_", (Standard_Boolean (*)(const opencascade::handle<Geom2d_Curve> &, const Standard_Real, const Standard_Real, TColgp_SequenceOfPnt2d &)) &ShapeAnalysis_Curve::GetSamplePoints, "Returns sample points which will serve as linearisation of the2d curve in range (first, last) The distribution of sample points is consystent with what is used by BRepTopAdaptor_FClass2d", py::arg("curve"), py::arg("first"), py::arg("last"), py::arg("seq"));
cls_ShapeAnalysis_Curve.def_static("GetSamplePoints_", (Standard_Boolean (*)(const opencascade::handle<Geom_Curve> &, const Standard_Real, const Standard_Real, TColgp_SequenceOfPnt &)) &ShapeAnalysis_Curve::GetSamplePoints, "Returns sample points which will serve as linearisation of the curve in range (first, last)", py::arg("curve"), py::arg("first"), py::arg("last"), py::arg("seq"));
cls_ShapeAnalysis_Curve.def_static("IsClosed_", [](const opencascade::handle<Geom_Curve> & a0) -> Standard_Boolean { return ShapeAnalysis_Curve::IsClosed(a0); });
cls_ShapeAnalysis_Curve.def_static("IsClosed_", (Standard_Boolean (*)(const opencascade::handle<Geom_Curve> &, const Standard_Real)) &ShapeAnalysis_Curve::IsClosed, "Tells if the Curve is closed with given precision. If <preci> < 0 then Precision::Confusion is used.", py::arg("curve"), py::arg("preci"));
cls_ShapeAnalysis_Curve.def_static("IsPeriodic_", (Standard_Boolean (*)(const opencascade::handle<Geom_Curve> &)) &ShapeAnalysis_Curve::IsPeriodic, "This method was implemented as fix for changes in trimmed curve behaviour. For the moment trimmed curve returns false anyway. So it is necessary to adapt all Data exchange tools for this behaviour. Current implementation takes into account that curve may be offset.", py::arg("curve"));
cls_ShapeAnalysis_Curve.def_static("IsPeriodic_", (Standard_Boolean (*)(const opencascade::handle<Geom2d_Curve> &)) &ShapeAnalysis_Curve::IsPeriodic, "The same as for Curve3d.", py::arg("curve"));

// CLASS: SHAPEANALYSIS_EDGE
py::class_<ShapeAnalysis_Edge> cls_ShapeAnalysis_Edge(mod, "ShapeAnalysis_Edge", "Tool for analyzing the edge. Queries geometrical representations of the edge (3d curve, pcurve on the given face or surface) and topological sub-shapes (bounding vertices). Provides methods for analyzing geometry and topology consistency (3d and pcurve(s) consistency, their adjacency to the vertices).");

// Constructors
cls_ShapeAnalysis_Edge.def(py::init<>());

// Methods
// cls_ShapeAnalysis_Edge.def_static("operator new_", (void * (*)(size_t)) &ShapeAnalysis_Edge::operator new, "None", py::arg("theSize"));
// cls_ShapeAnalysis_Edge.def_static("operator delete_", (void (*)(void *)) &ShapeAnalysis_Edge::operator delete, "None", py::arg("theAddress"));
// cls_ShapeAnalysis_Edge.def_static("operator new[]_", (void * (*)(size_t)) &ShapeAnalysis_Edge::operator new[], "None", py::arg("theSize"));
// cls_ShapeAnalysis_Edge.def_static("operator delete[]_", (void (*)(void *)) &ShapeAnalysis_Edge::operator delete[], "None", py::arg("theAddress"));
// cls_ShapeAnalysis_Edge.def_static("operator new_", (void * (*)(size_t, void *)) &ShapeAnalysis_Edge::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ShapeAnalysis_Edge.def_static("operator delete_", (void (*)(void *, void *)) &ShapeAnalysis_Edge::operator delete, "None", py::arg(""), py::arg(""));
cls_ShapeAnalysis_Edge.def("HasCurve3d", (Standard_Boolean (ShapeAnalysis_Edge::*)(const TopoDS_Edge &) const) &ShapeAnalysis_Edge::HasCurve3d, "Tells if the edge has a 3d curve", py::arg("edge"));
cls_ShapeAnalysis_Edge.def("Curve3d", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & edge, opencascade::handle<Geom_Curve> & C3d, Standard_Real & cf, Standard_Real & cl, const Standard_Boolean orient){ Standard_Boolean rv = self.Curve3d(edge, C3d, cf, cl, orient); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &>(rv, cf, cl); }, "Returns the 3d curve and bounding parameteres for the edge Returns False if no 3d curve. If <orient> is True (default), takes orientation into account: if the edge is reversed, cf and cl are toggled", py::arg("edge"), py::arg("C3d"), py::arg("cf"), py::arg("cl"), py::arg("orient"));
cls_ShapeAnalysis_Edge.def("IsClosed3d", (Standard_Boolean (ShapeAnalysis_Edge::*)(const TopoDS_Edge &) const) &ShapeAnalysis_Edge::IsClosed3d, "Gives True if the edge has a 3d curve, this curve is closed, and the edge has the same vertex at start and end", py::arg("edge"));
cls_ShapeAnalysis_Edge.def("HasPCurve", (Standard_Boolean (ShapeAnalysis_Edge::*)(const TopoDS_Edge &, const TopoDS_Face &) const) &ShapeAnalysis_Edge::HasPCurve, "Tells if the Edge has a pcurve on the face.", py::arg("edge"), py::arg("face"));
cls_ShapeAnalysis_Edge.def("HasPCurve", (Standard_Boolean (ShapeAnalysis_Edge::*)(const TopoDS_Edge &, const opencascade::handle<Geom_Surface> &, const TopLoc_Location &) const) &ShapeAnalysis_Edge::HasPCurve, "Tells if the edge has a pcurve on the surface (with location).", py::arg("edge"), py::arg("surface"), py::arg("location"));
cls_ShapeAnalysis_Edge.def("PCurve", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & edge, const TopoDS_Face & face, opencascade::handle<Geom2d_Curve> & C2d, Standard_Real & cf, Standard_Real & cl, const Standard_Boolean orient){ Standard_Boolean rv = self.PCurve(edge, face, C2d, cf, cl, orient); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &>(rv, cf, cl); }, "None", py::arg("edge"), py::arg("face"), py::arg("C2d"), py::arg("cf"), py::arg("cl"), py::arg("orient"));
cls_ShapeAnalysis_Edge.def("PCurve", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & edge, const opencascade::handle<Geom_Surface> & surface, const TopLoc_Location & location, opencascade::handle<Geom2d_Curve> & C2d, Standard_Real & cf, Standard_Real & cl, const Standard_Boolean orient){ Standard_Boolean rv = self.PCurve(edge, surface, location, C2d, cf, cl, orient); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &>(rv, cf, cl); }, "Returns the pcurve and bounding parameteres for the edge lying on the surface. Returns False if the edge has no pcurve on this surface. If <orient> is True (default), takes orientation into account: if the edge is reversed, cf and cl are toggled", py::arg("edge"), py::arg("surface"), py::arg("location"), py::arg("C2d"), py::arg("cf"), py::arg("cl"), py::arg("orient"));
cls_ShapeAnalysis_Edge.def("BoundUV", (Standard_Boolean (ShapeAnalysis_Edge::*)(const TopoDS_Edge &, const TopoDS_Face &, gp_Pnt2d &, gp_Pnt2d &) const) &ShapeAnalysis_Edge::BoundUV, "None", py::arg("edge"), py::arg("face"), py::arg("first"), py::arg("last"));
cls_ShapeAnalysis_Edge.def("BoundUV", (Standard_Boolean (ShapeAnalysis_Edge::*)(const TopoDS_Edge &, const opencascade::handle<Geom_Surface> &, const TopLoc_Location &, gp_Pnt2d &, gp_Pnt2d &) const) &ShapeAnalysis_Edge::BoundUV, "Returns the ends of pcurve Calls method PCurve with <orient> equal to True", py::arg("edge"), py::arg("surface"), py::arg("location"), py::arg("first"), py::arg("last"));
cls_ShapeAnalysis_Edge.def("IsSeam", (Standard_Boolean (ShapeAnalysis_Edge::*)(const TopoDS_Edge &, const TopoDS_Face &) const) &ShapeAnalysis_Edge::IsSeam, "None", py::arg("edge"), py::arg("face"));
cls_ShapeAnalysis_Edge.def("IsSeam", (Standard_Boolean (ShapeAnalysis_Edge::*)(const TopoDS_Edge &, const opencascade::handle<Geom_Surface> &, const TopLoc_Location &) const) &ShapeAnalysis_Edge::IsSeam, "Returns True if the edge has two pcurves on one surface", py::arg("edge"), py::arg("surface"), py::arg("location"));
cls_ShapeAnalysis_Edge.def("FirstVertex", (TopoDS_Vertex (ShapeAnalysis_Edge::*)(const TopoDS_Edge &) const) &ShapeAnalysis_Edge::FirstVertex, "Returns start vertex of the edge (taking edge orientation into account).", py::arg("edge"));
cls_ShapeAnalysis_Edge.def("LastVertex", (TopoDS_Vertex (ShapeAnalysis_Edge::*)(const TopoDS_Edge &) const) &ShapeAnalysis_Edge::LastVertex, "Returns end vertex of the edge (taking edge orientation into account).", py::arg("edge"));
cls_ShapeAnalysis_Edge.def("GetEndTangent2d", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & a0, const TopoDS_Face & a1, const Standard_Boolean a2, gp_Pnt2d & a3, gp_Vec2d & a4) -> Standard_Boolean { return self.GetEndTangent2d(a0, a1, a2, a3, a4); });
cls_ShapeAnalysis_Edge.def("GetEndTangent2d", (Standard_Boolean (ShapeAnalysis_Edge::*)(const TopoDS_Edge &, const TopoDS_Face &, const Standard_Boolean, gp_Pnt2d &, gp_Vec2d &, const Standard_Real) const) &ShapeAnalysis_Edge::GetEndTangent2d, "None", py::arg("edge"), py::arg("face"), py::arg("atEnd"), py::arg("pos"), py::arg("tang"), py::arg("dparam"));
cls_ShapeAnalysis_Edge.def("GetEndTangent2d", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & a0, const opencascade::handle<Geom_Surface> & a1, const TopLoc_Location & a2, const Standard_Boolean a3, gp_Pnt2d & a4, gp_Vec2d & a5) -> Standard_Boolean { return self.GetEndTangent2d(a0, a1, a2, a3, a4, a5); });
cls_ShapeAnalysis_Edge.def("GetEndTangent2d", (Standard_Boolean (ShapeAnalysis_Edge::*)(const TopoDS_Edge &, const opencascade::handle<Geom_Surface> &, const TopLoc_Location &, const Standard_Boolean, gp_Pnt2d &, gp_Vec2d &, const Standard_Real) const) &ShapeAnalysis_Edge::GetEndTangent2d, "Returns tangent of the edge pcurve at its start (if atEnd is False) or end (if True), regarding the orientation of edge. If edge is REVERSED, tangent is reversed before return. Returns True if pcurve is available and tangent is computed and is not null, else False.", py::arg("edge"), py::arg("surface"), py::arg("location"), py::arg("atEnd"), py::arg("pos"), py::arg("tang"), py::arg("dparam"));
cls_ShapeAnalysis_Edge.def("CheckVerticesWithCurve3d", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & a0) -> Standard_Boolean { return self.CheckVerticesWithCurve3d(a0); });
cls_ShapeAnalysis_Edge.def("CheckVerticesWithCurve3d", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & a0, const Standard_Real a1) -> Standard_Boolean { return self.CheckVerticesWithCurve3d(a0, a1); });
cls_ShapeAnalysis_Edge.def("CheckVerticesWithCurve3d", (Standard_Boolean (ShapeAnalysis_Edge::*)(const TopoDS_Edge &, const Standard_Real, const Standard_Integer)) &ShapeAnalysis_Edge::CheckVerticesWithCurve3d, "Checks the start and/or end vertex of the edge for matching with 3d curve with the given precision. <vtx> = 1 : start vertex only <vtx> = 2 : end vertex only <vtx> = 0 : both (default) If preci < 0 the vertices are considered with their own tolerances, else with the given <preci>.", py::arg("edge"), py::arg("preci"), py::arg("vtx"));
cls_ShapeAnalysis_Edge.def("CheckVerticesWithPCurve", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & a0, const TopoDS_Face & a1) -> Standard_Boolean { return self.CheckVerticesWithPCurve(a0, a1); });
cls_ShapeAnalysis_Edge.def("CheckVerticesWithPCurve", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & a0, const TopoDS_Face & a1, const Standard_Real a2) -> Standard_Boolean { return self.CheckVerticesWithPCurve(a0, a1, a2); });
cls_ShapeAnalysis_Edge.def("CheckVerticesWithPCurve", (Standard_Boolean (ShapeAnalysis_Edge::*)(const TopoDS_Edge &, const TopoDS_Face &, const Standard_Real, const Standard_Integer)) &ShapeAnalysis_Edge::CheckVerticesWithPCurve, "None", py::arg("edge"), py::arg("face"), py::arg("preci"), py::arg("vtx"));
cls_ShapeAnalysis_Edge.def("CheckVerticesWithPCurve", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & a0, const opencascade::handle<Geom_Surface> & a1, const TopLoc_Location & a2) -> Standard_Boolean { return self.CheckVerticesWithPCurve(a0, a1, a2); });
cls_ShapeAnalysis_Edge.def("CheckVerticesWithPCurve", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & a0, const opencascade::handle<Geom_Surface> & a1, const TopLoc_Location & a2, const Standard_Real a3) -> Standard_Boolean { return self.CheckVerticesWithPCurve(a0, a1, a2, a3); });
cls_ShapeAnalysis_Edge.def("CheckVerticesWithPCurve", (Standard_Boolean (ShapeAnalysis_Edge::*)(const TopoDS_Edge &, const opencascade::handle<Geom_Surface> &, const TopLoc_Location &, const Standard_Real, const Standard_Integer)) &ShapeAnalysis_Edge::CheckVerticesWithPCurve, "Checks the start and/or end vertex of the edge for matching with pcurve with the given precision. <vtx> = 1 : start vertex <vtx> = 2 : end vertex <vtx> = 0 : both If preci < 0 the vertices are considered with their own tolerances, else with the given <preci>.", py::arg("edge"), py::arg("surface"), py::arg("location"), py::arg("preci"), py::arg("vtx"));
cls_ShapeAnalysis_Edge.def("CheckVertexTolerance", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & edge, const TopoDS_Face & face, Standard_Real & toler1, Standard_Real & toler2){ Standard_Boolean rv = self.CheckVertexTolerance(edge, face, toler1, toler2); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &>(rv, toler1, toler2); }, "None", py::arg("edge"), py::arg("face"), py::arg("toler1"), py::arg("toler2"));
cls_ShapeAnalysis_Edge.def("CheckVertexTolerance", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & edge, Standard_Real & toler1, Standard_Real & toler2){ Standard_Boolean rv = self.CheckVertexTolerance(edge, toler1, toler2); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &>(rv, toler1, toler2); }, "Checks if it is necessary to increase tolerances of the edge vertices to comprise the ends of 3d curve and pcurve on the given face (first method) or all pcurves stored in an edge (second one) toler1 returns necessary tolerance for first vertex, toler2 returns necessary tolerance for last vertex.", py::arg("edge"), py::arg("toler1"), py::arg("toler2"));
cls_ShapeAnalysis_Edge.def("CheckCurve3dWithPCurve", (Standard_Boolean (ShapeAnalysis_Edge::*)(const TopoDS_Edge &, const TopoDS_Face &)) &ShapeAnalysis_Edge::CheckCurve3dWithPCurve, "None", py::arg("edge"), py::arg("face"));
cls_ShapeAnalysis_Edge.def("CheckCurve3dWithPCurve", (Standard_Boolean (ShapeAnalysis_Edge::*)(const TopoDS_Edge &, const opencascade::handle<Geom_Surface> &, const TopLoc_Location &)) &ShapeAnalysis_Edge::CheckCurve3dWithPCurve, "Checks mutual orientation of 3d curve and pcurve on the analysis of curves bounding points", py::arg("edge"), py::arg("surface"), py::arg("location"));
cls_ShapeAnalysis_Edge.def("Status", (Standard_Boolean (ShapeAnalysis_Edge::*)(const ShapeExtend_Status) const) &ShapeAnalysis_Edge::Status, "Returns the status (in the form of True/False) of last Check", py::arg("status"));
cls_ShapeAnalysis_Edge.def("CheckSameParameter", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & edge, Standard_Real & maxdev, const Standard_Integer NbControl){ Standard_Boolean rv = self.CheckSameParameter(edge, maxdev, NbControl); return std::tuple<Standard_Boolean, Standard_Real &>(rv, maxdev); }, "Checks the edge to be SameParameter. Calculates the maximal deviation between 3d curve and each pcurve of the edge on <NbControl> equidistant points (the same algorithm as in BRepCheck; default value is 23 as in BRepCheck). This deviation is returned in <maxdev> parameter. If deviation is greater than tolerance of the edge (i.e. incorrect flag) returns False, else returns True.", py::arg("edge"), py::arg("maxdev"), py::arg("NbControl"));
cls_ShapeAnalysis_Edge.def("CheckSameParameter", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & theEdge, const TopoDS_Face & theFace, Standard_Real & theMaxdev, const Standard_Integer theNbControl){ Standard_Boolean rv = self.CheckSameParameter(theEdge, theFace, theMaxdev, theNbControl); return std::tuple<Standard_Boolean, Standard_Real &>(rv, theMaxdev); }, "Checks the edge to be SameParameter. Calculates the maximal deviation between 3d curve and each pcurve of the edge on <NbControl> equidistant points (the same algorithm as in BRepCheck; default value is 23 as in BRepCheck). This deviation is returned in <maxdev> parameter. If deviation is greater than tolerance of the edge (i.e. incorrect flag) returns False, else returns True.", py::arg("theEdge"), py::arg("theFace"), py::arg("theMaxdev"), py::arg("theNbControl"));
cls_ShapeAnalysis_Edge.def("CheckPCurveRange", (Standard_Boolean (ShapeAnalysis_Edge::*)(const Standard_Real, const Standard_Real, const opencascade::handle<Geom2d_Curve> &)) &ShapeAnalysis_Edge::CheckPCurveRange, "Checks possibility for pcurve thePC to have range [theFirst, theLast] (edge range) having respect to real first, last parameters of thePC", py::arg("theFirst"), py::arg("theLast"), py::arg("thePC"));
cls_ShapeAnalysis_Edge.def_static("ComputeDeviation_", [](const Adaptor3d_Curve & CRef, const Adaptor3d_Curve & Other, const Standard_Boolean SameParameter, Standard_Real & dev, const Standard_Integer NCONTROL){ Standard_Boolean rv = ShapeAnalysis_Edge::ComputeDeviation(CRef, Other, SameParameter, dev, NCONTROL); return std::tuple<Standard_Boolean, Standard_Real &>(rv, dev); }, "Computes the maximal deviation between the two curve representations. dev is an input/output parameter and contains the computed deviation (should be initialized with 0. for the first call). Used by CheckSameParameter().", py::arg("CRef"), py::arg("Other"), py::arg("SameParameter"), py::arg("dev"), py::arg("NCONTROL"));
cls_ShapeAnalysis_Edge.def("CheckOverlapping", [](ShapeAnalysis_Edge &self, const TopoDS_Edge & theEdge1, const TopoDS_Edge & theEdge2, Standard_Real & theTolOverlap, const Standard_Real theDomainDist){ Standard_Boolean rv = self.CheckOverlapping(theEdge1, theEdge2, theTolOverlap, theDomainDist); return std::tuple<Standard_Boolean, Standard_Real &>(rv, theTolOverlap); }, "Checks the first edge is overlapped with second edge. If distance between two edges is less then theTolOverlap edges is overlapped. theDomainDis - length of part of edges on wich edges is overlapped.", py::arg("theEdge1"), py::arg("theEdge2"), py::arg("theTolOverlap"), py::arg("theDomainDist"));

// CLASS: SHAPEANALYSIS_FREEBOUNDDATA
py::class_<ShapeAnalysis_FreeBoundData, opencascade::handle<ShapeAnalysis_FreeBoundData>, Standard_Transient> cls_ShapeAnalysis_FreeBoundData(mod, "ShapeAnalysis_FreeBoundData", "This class is intended to represent free bound and to store its properties.");

// Constructors
cls_ShapeAnalysis_FreeBoundData.def(py::init<>());
cls_ShapeAnalysis_FreeBoundData.def(py::init<const TopoDS_Wire &>(), py::arg("freebound"));

// Methods
cls_ShapeAnalysis_FreeBoundData.def("Clear", (void (ShapeAnalysis_FreeBoundData::*)()) &ShapeAnalysis_FreeBoundData::Clear, "Clears all properties of the contour. Contour bound itself is not cleared.");
cls_ShapeAnalysis_FreeBoundData.def("SetFreeBound", (void (ShapeAnalysis_FreeBoundData::*)(const TopoDS_Wire &)) &ShapeAnalysis_FreeBoundData::SetFreeBound, "Sets contour", py::arg("freebound"));
cls_ShapeAnalysis_FreeBoundData.def("SetArea", (void (ShapeAnalysis_FreeBoundData::*)(const Standard_Real)) &ShapeAnalysis_FreeBoundData::SetArea, "Sets area of the contour", py::arg("area"));
cls_ShapeAnalysis_FreeBoundData.def("SetPerimeter", (void (ShapeAnalysis_FreeBoundData::*)(const Standard_Real)) &ShapeAnalysis_FreeBoundData::SetPerimeter, "Sets perimeter of the contour", py::arg("perimeter"));
cls_ShapeAnalysis_FreeBoundData.def("SetRatio", (void (ShapeAnalysis_FreeBoundData::*)(const Standard_Real)) &ShapeAnalysis_FreeBoundData::SetRatio, "Sets ratio of average length to average width of the contour", py::arg("ratio"));
cls_ShapeAnalysis_FreeBoundData.def("SetWidth", (void (ShapeAnalysis_FreeBoundData::*)(const Standard_Real)) &ShapeAnalysis_FreeBoundData::SetWidth, "Sets average width of the contour", py::arg("width"));
cls_ShapeAnalysis_FreeBoundData.def("AddNotch", (void (ShapeAnalysis_FreeBoundData::*)(const TopoDS_Wire &, const Standard_Real)) &ShapeAnalysis_FreeBoundData::AddNotch, "Adds notch on the contour with its maximum width", py::arg("notch"), py::arg("width"));
cls_ShapeAnalysis_FreeBoundData.def("FreeBound", (TopoDS_Wire (ShapeAnalysis_FreeBoundData::*)() const) &ShapeAnalysis_FreeBoundData::FreeBound, "Returns contour");
cls_ShapeAnalysis_FreeBoundData.def("Area", (Standard_Real (ShapeAnalysis_FreeBoundData::*)() const) &ShapeAnalysis_FreeBoundData::Area, "Returns area of the contour");
cls_ShapeAnalysis_FreeBoundData.def("Perimeter", (Standard_Real (ShapeAnalysis_FreeBoundData::*)() const) &ShapeAnalysis_FreeBoundData::Perimeter, "Returns perimeter of the contour");
cls_ShapeAnalysis_FreeBoundData.def("Ratio", (Standard_Real (ShapeAnalysis_FreeBoundData::*)() const) &ShapeAnalysis_FreeBoundData::Ratio, "Returns ratio of average length to average width of the contour");
cls_ShapeAnalysis_FreeBoundData.def("Width", (Standard_Real (ShapeAnalysis_FreeBoundData::*)() const) &ShapeAnalysis_FreeBoundData::Width, "Returns average width of the contour");
cls_ShapeAnalysis_FreeBoundData.def("NbNotches", (Standard_Integer (ShapeAnalysis_FreeBoundData::*)() const) &ShapeAnalysis_FreeBoundData::NbNotches, "Returns number of notches on the contour");
cls_ShapeAnalysis_FreeBoundData.def("Notches", (opencascade::handle<TopTools_HSequenceOfShape> (ShapeAnalysis_FreeBoundData::*)() const) &ShapeAnalysis_FreeBoundData::Notches, "Returns sequence of notches on the contour");
cls_ShapeAnalysis_FreeBoundData.def("Notch", (TopoDS_Wire (ShapeAnalysis_FreeBoundData::*)(const Standard_Integer) const) &ShapeAnalysis_FreeBoundData::Notch, "Returns notch on the contour", py::arg("index"));
cls_ShapeAnalysis_FreeBoundData.def("NotchWidth", (Standard_Real (ShapeAnalysis_FreeBoundData::*)(const Standard_Integer) const) &ShapeAnalysis_FreeBoundData::NotchWidth, "Returns maximum width of notch specified by its rank number on the contour", py::arg("index"));
cls_ShapeAnalysis_FreeBoundData.def("NotchWidth", (Standard_Real (ShapeAnalysis_FreeBoundData::*)(const TopoDS_Wire &) const) &ShapeAnalysis_FreeBoundData::NotchWidth, "Returns maximum width of notch specified as TopoDS_Wire on the contour", py::arg("notch"));
cls_ShapeAnalysis_FreeBoundData.def_static("get_type_name_", (const char * (*)()) &ShapeAnalysis_FreeBoundData::get_type_name, "None");
cls_ShapeAnalysis_FreeBoundData.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &ShapeAnalysis_FreeBoundData::get_type_descriptor, "None");
cls_ShapeAnalysis_FreeBoundData.def("DynamicType", (const opencascade::handle<Standard_Type> & (ShapeAnalysis_FreeBoundData::*)() const) &ShapeAnalysis_FreeBoundData::DynamicType, "None");

// CLASS: SHAPEANALYSIS_FREEBOUNDS
py::class_<ShapeAnalysis_FreeBounds> cls_ShapeAnalysis_FreeBounds(mod, "ShapeAnalysis_FreeBounds", "This class is intended to output free bounds of the shape (free bounds are the wires consisting of edges referenced by the only face). This class works on two distinct types of shapes when analyzing their free bounds: 1. compound of faces. Analyzer of sewing algorithm (BRepAlgo_Sewing) is used for for forecasting free bounds that would be obtained after performing sewing 2. compound of shells. Actual free bounds (edges shared by the only face in the shell) are output in this case. ShapeAnalysis_Shell is used for that.");

// Constructors
cls_ShapeAnalysis_FreeBounds.def(py::init<>());
cls_ShapeAnalysis_FreeBounds.def(py::init<const TopoDS_Shape &, const Standard_Real>(), py::arg("shape"), py::arg("toler"));
cls_ShapeAnalysis_FreeBounds.def(py::init<const TopoDS_Shape &, const Standard_Real, const Standard_Boolean>(), py::arg("shape"), py::arg("toler"), py::arg("splitclosed"));
cls_ShapeAnalysis_FreeBounds.def(py::init<const TopoDS_Shape &, const Standard_Real, const Standard_Boolean, const Standard_Boolean>(), py::arg("shape"), py::arg("toler"), py::arg("splitclosed"), py::arg("splitopen"));
cls_ShapeAnalysis_FreeBounds.def(py::init<const TopoDS_Shape &>(), py::arg("shape"));
cls_ShapeAnalysis_FreeBounds.def(py::init<const TopoDS_Shape &, const Standard_Boolean>(), py::arg("shape"), py::arg("splitclosed"));
cls_ShapeAnalysis_FreeBounds.def(py::init<const TopoDS_Shape &, const Standard_Boolean, const Standard_Boolean>(), py::arg("shape"), py::arg("splitclosed"), py::arg("splitopen"));
cls_ShapeAnalysis_FreeBounds.def(py::init<const TopoDS_Shape &, const Standard_Boolean, const Standard_Boolean, const Standard_Boolean>(), py::arg("shape"), py::arg("splitclosed"), py::arg("splitopen"), py::arg("checkinternaledges"));

// Methods
// cls_ShapeAnalysis_FreeBounds.def_static("operator new_", (void * (*)(size_t)) &ShapeAnalysis_FreeBounds::operator new, "None", py::arg("theSize"));
// cls_ShapeAnalysis_FreeBounds.def_static("operator delete_", (void (*)(void *)) &ShapeAnalysis_FreeBounds::operator delete, "None", py::arg("theAddress"));
// cls_ShapeAnalysis_FreeBounds.def_static("operator new[]_", (void * (*)(size_t)) &ShapeAnalysis_FreeBounds::operator new[], "None", py::arg("theSize"));
// cls_ShapeAnalysis_FreeBounds.def_static("operator delete[]_", (void (*)(void *)) &ShapeAnalysis_FreeBounds::operator delete[], "None", py::arg("theAddress"));
// cls_ShapeAnalysis_FreeBounds.def_static("operator new_", (void * (*)(size_t, void *)) &ShapeAnalysis_FreeBounds::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ShapeAnalysis_FreeBounds.def_static("operator delete_", (void (*)(void *, void *)) &ShapeAnalysis_FreeBounds::operator delete, "None", py::arg(""), py::arg(""));
cls_ShapeAnalysis_FreeBounds.def("GetClosedWires", (const TopoDS_Compound & (ShapeAnalysis_FreeBounds::*)() const) &ShapeAnalysis_FreeBounds::GetClosedWires, "Returns compound of closed wires out of free edges.");
cls_ShapeAnalysis_FreeBounds.def("GetOpenWires", (const TopoDS_Compound & (ShapeAnalysis_FreeBounds::*)() const) &ShapeAnalysis_FreeBounds::GetOpenWires, "Returns compound of open wires out of free edges.");
cls_ShapeAnalysis_FreeBounds.def_static("ConnectEdgesToWires_", (void (*)(opencascade::handle<TopTools_HSequenceOfShape> &, const Standard_Real, const Standard_Boolean, opencascade::handle<TopTools_HSequenceOfShape> &)) &ShapeAnalysis_FreeBounds::ConnectEdgesToWires, "Builds sequnce of <wires> out of sequence of not sorted <edges>. Tries to build wires of maximum length. Building a wire is stopped when no edges can be connected to it at its head or at its tail.", py::arg("edges"), py::arg("toler"), py::arg("shared"), py::arg("wires"));
cls_ShapeAnalysis_FreeBounds.def_static("ConnectWiresToWires_", (void (*)(opencascade::handle<TopTools_HSequenceOfShape> &, const Standard_Real, const Standard_Boolean, opencascade::handle<TopTools_HSequenceOfShape> &)) &ShapeAnalysis_FreeBounds::ConnectWiresToWires, "None", py::arg("iwires"), py::arg("toler"), py::arg("shared"), py::arg("owires"));
cls_ShapeAnalysis_FreeBounds.def_static("ConnectWiresToWires_", (void (*)(opencascade::handle<TopTools_HSequenceOfShape> &, const Standard_Real, const Standard_Boolean, opencascade::handle<TopTools_HSequenceOfShape> &, TopTools_DataMapOfShapeShape &)) &ShapeAnalysis_FreeBounds::ConnectWiresToWires, "Builds sequnce of <owires> out of sequence of not sorted <iwires>. Tries to build wires of maximum length. Building a wire is stopped when no wires can be connected to it at its head or at its tail.", py::arg("iwires"), py::arg("toler"), py::arg("shared"), py::arg("owires"), py::arg("vertices"));
cls_ShapeAnalysis_FreeBounds.def_static("SplitWires_", (void (*)(const opencascade::handle<TopTools_HSequenceOfShape> &, const Standard_Real, const Standard_Boolean, opencascade::handle<TopTools_HSequenceOfShape> &, opencascade::handle<TopTools_HSequenceOfShape> &)) &ShapeAnalysis_FreeBounds::SplitWires, "Extracts closed sub-wires out of <wires> and adds them to <closed>, open wires remained after extraction are put into <open>. If <shared> is True extraction is performed only when edges share the same vertex. If <shared> is False connection is performed only when ends of the edges are at distance less than <toler>.", py::arg("wires"), py::arg("toler"), py::arg("shared"), py::arg("closed"), py::arg("open"));
cls_ShapeAnalysis_FreeBounds.def_static("DispatchWires_", (void (*)(const opencascade::handle<TopTools_HSequenceOfShape> &, TopoDS_Compound &, TopoDS_Compound &)) &ShapeAnalysis_FreeBounds::DispatchWires, "Dispatches sequence of <wires> into two compounds <closed> for closed wires and <open> for open wires. If a compound is not empty wires are added into it.", py::arg("wires"), py::arg("closed"), py::arg("open"));

// TYPEDEF: SHAPEANALYSIS_SEQUENCEOFFREEBOUNDS
bind_NCollection_Sequence<opencascade::handle<ShapeAnalysis_FreeBoundData> >(mod, "ShapeAnalysis_SequenceOfFreeBounds", py::module_local(false));

// CLASS: SHAPEANALYSIS_HSEQUENCEOFFREEBOUNDS
py::class_<ShapeAnalysis_HSequenceOfFreeBounds, opencascade::handle<ShapeAnalysis_HSequenceOfFreeBounds>, Standard_Transient> cls_ShapeAnalysis_HSequenceOfFreeBounds(mod, "ShapeAnalysis_HSequenceOfFreeBounds", "None", py::multiple_inheritance());

// Constructors
cls_ShapeAnalysis_HSequenceOfFreeBounds.def(py::init<>());
cls_ShapeAnalysis_HSequenceOfFreeBounds.def(py::init<const ShapeAnalysis_SequenceOfFreeBounds &>(), py::arg("theOther"));

// Methods
// cls_ShapeAnalysis_HSequenceOfFreeBounds.def_static("operator new_", (void * (*)(size_t)) &ShapeAnalysis_HSequenceOfFreeBounds::operator new, "None", py::arg("theSize"));
// cls_ShapeAnalysis_HSequenceOfFreeBounds.def_static("operator delete_", (void (*)(void *)) &ShapeAnalysis_HSequenceOfFreeBounds::operator delete, "None", py::arg("theAddress"));
// cls_ShapeAnalysis_HSequenceOfFreeBounds.def_static("operator new[]_", (void * (*)(size_t)) &ShapeAnalysis_HSequenceOfFreeBounds::operator new[], "None", py::arg("theSize"));
// cls_ShapeAnalysis_HSequenceOfFreeBounds.def_static("operator delete[]_", (void (*)(void *)) &ShapeAnalysis_HSequenceOfFreeBounds::operator delete[], "None", py::arg("theAddress"));
// cls_ShapeAnalysis_HSequenceOfFreeBounds.def_static("operator new_", (void * (*)(size_t, void *)) &ShapeAnalysis_HSequenceOfFreeBounds::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ShapeAnalysis_HSequenceOfFreeBounds.def_static("operator delete_", (void (*)(void *, void *)) &ShapeAnalysis_HSequenceOfFreeBounds::operator delete, "None", py::arg(""), py::arg(""));
// cls_ShapeAnalysis_HSequenceOfFreeBounds.def_static("operator new_", (void * (*)(size_t, const opencascade::handle<NCollection_BaseAllocator> &)) &ShapeAnalysis_HSequenceOfFreeBounds::operator new, "None", py::arg("theSize"), py::arg("theAllocator"));
// cls_ShapeAnalysis_HSequenceOfFreeBounds.def_static("operator delete_", (void (*)(void *, const opencascade::handle<NCollection_BaseAllocator> &)) &ShapeAnalysis_HSequenceOfFreeBounds::operator delete, "None", py::arg("theAddress"), py::arg("theAllocator"));
cls_ShapeAnalysis_HSequenceOfFreeBounds.def("Sequence", (const ShapeAnalysis_SequenceOfFreeBounds & (ShapeAnalysis_HSequenceOfFreeBounds::*)() const) &ShapeAnalysis_HSequenceOfFreeBounds::Sequence, "None");
cls_ShapeAnalysis_HSequenceOfFreeBounds.def("Append", (void (ShapeAnalysis_HSequenceOfFreeBounds::*)(const ShapeAnalysis_SequenceOfFreeBounds::value_type &)) &ShapeAnalysis_HSequenceOfFreeBounds::Append, "None", py::arg("theItem"));
cls_ShapeAnalysis_HSequenceOfFreeBounds.def("Append", (void (ShapeAnalysis_HSequenceOfFreeBounds::*)(ShapeAnalysis_SequenceOfFreeBounds &)) &ShapeAnalysis_HSequenceOfFreeBounds::Append, "None", py::arg("theSequence"));
cls_ShapeAnalysis_HSequenceOfFreeBounds.def("ChangeSequence", (ShapeAnalysis_SequenceOfFreeBounds & (ShapeAnalysis_HSequenceOfFreeBounds::*)()) &ShapeAnalysis_HSequenceOfFreeBounds::ChangeSequence, "None");
cls_ShapeAnalysis_HSequenceOfFreeBounds.def_static("get_type_name_", (const char * (*)()) &ShapeAnalysis_HSequenceOfFreeBounds::get_type_name, "None");
cls_ShapeAnalysis_HSequenceOfFreeBounds.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &ShapeAnalysis_HSequenceOfFreeBounds::get_type_descriptor, "None");
cls_ShapeAnalysis_HSequenceOfFreeBounds.def("DynamicType", (const opencascade::handle<Standard_Type> & (ShapeAnalysis_HSequenceOfFreeBounds::*)() const) &ShapeAnalysis_HSequenceOfFreeBounds::DynamicType, "None");

// CLASS: SHAPEANALYSIS_FREEBOUNDSPROPERTIES
py::class_<ShapeAnalysis_FreeBoundsProperties> cls_ShapeAnalysis_FreeBoundsProperties(mod, "ShapeAnalysis_FreeBoundsProperties", "This class is intended to calculate shape free bounds properties. This class provides the following functionalities: - calculates area of the contour, - calculates perimeter of the contour, - calculates ratio of average length to average width of the contour, - estimates average width of contour, - finds the notches (narrow 'V'-like sub-contour) on the contour.");

// Constructors
cls_ShapeAnalysis_FreeBoundsProperties.def(py::init<>());
cls_ShapeAnalysis_FreeBoundsProperties.def(py::init<const TopoDS_Shape &, const Standard_Real>(), py::arg("shape"), py::arg("tolerance"));
cls_ShapeAnalysis_FreeBoundsProperties.def(py::init<const TopoDS_Shape &, const Standard_Real, const Standard_Boolean>(), py::arg("shape"), py::arg("tolerance"), py::arg("splitclosed"));
cls_ShapeAnalysis_FreeBoundsProperties.def(py::init<const TopoDS_Shape &, const Standard_Real, const Standard_Boolean, const Standard_Boolean>(), py::arg("shape"), py::arg("tolerance"), py::arg("splitclosed"), py::arg("splitopen"));
cls_ShapeAnalysis_FreeBoundsProperties.def(py::init<const TopoDS_Shape &>(), py::arg("shape"));
cls_ShapeAnalysis_FreeBoundsProperties.def(py::init<const TopoDS_Shape &, const Standard_Boolean>(), py::arg("shape"), py::arg("splitclosed"));
cls_ShapeAnalysis_FreeBoundsProperties.def(py::init<const TopoDS_Shape &, const Standard_Boolean, const Standard_Boolean>(), py::arg("shape"), py::arg("splitclosed"), py::arg("splitopen"));

// Methods
// cls_ShapeAnalysis_FreeBoundsProperties.def_static("operator new_", (void * (*)(size_t)) &ShapeAnalysis_FreeBoundsProperties::operator new, "None", py::arg("theSize"));
// cls_ShapeAnalysis_FreeBoundsProperties.def_static("operator delete_", (void (*)(void *)) &ShapeAnalysis_FreeBoundsProperties::operator delete, "None", py::arg("theAddress"));
// cls_ShapeAnalysis_FreeBoundsProperties.def_static("operator new[]_", (void * (*)(size_t)) &ShapeAnalysis_FreeBoundsProperties::operator new[], "None", py::arg("theSize"));
// cls_ShapeAnalysis_FreeBoundsProperties.def_static("operator delete[]_", (void (*)(void *)) &ShapeAnalysis_FreeBoundsProperties::operator delete[], "None", py::arg("theAddress"));
// cls_ShapeAnalysis_FreeBoundsProperties.def_static("operator new_", (void * (*)(size_t, void *)) &ShapeAnalysis_FreeBoundsProperties::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ShapeAnalysis_FreeBoundsProperties.def_static("operator delete_", (void (*)(void *, void *)) &ShapeAnalysis_FreeBoundsProperties::operator delete, "None", py::arg(""), py::arg(""));
cls_ShapeAnalysis_FreeBoundsProperties.def("Init", [](ShapeAnalysis_FreeBoundsProperties &self, const TopoDS_Shape & a0, const Standard_Real a1) -> void { return self.Init(a0, a1); });
cls_ShapeAnalysis_FreeBoundsProperties.def("Init", [](ShapeAnalysis_FreeBoundsProperties &self, const TopoDS_Shape & a0, const Standard_Real a1, const Standard_Boolean a2) -> void { return self.Init(a0, a1, a2); });
cls_ShapeAnalysis_FreeBoundsProperties.def("Init", (void (ShapeAnalysis_FreeBoundsProperties::*)(const TopoDS_Shape &, const Standard_Real, const Standard_Boolean, const Standard_Boolean)) &ShapeAnalysis_FreeBoundsProperties::Init, "Initializes the object with given parameters. <shape> should be a compound of faces.", py::arg("shape"), py::arg("tolerance"), py::arg("splitclosed"), py::arg("splitopen"));
cls_ShapeAnalysis_FreeBoundsProperties.def("Init", [](ShapeAnalysis_FreeBoundsProperties &self, const TopoDS_Shape & a0) -> void { return self.Init(a0); });
cls_ShapeAnalysis_FreeBoundsProperties.def("Init", [](ShapeAnalysis_FreeBoundsProperties &self, const TopoDS_Shape & a0, const Standard_Boolean a1) -> void { return self.Init(a0, a1); });
cls_ShapeAnalysis_FreeBoundsProperties.def("Init", (void (ShapeAnalysis_FreeBoundsProperties::*)(const TopoDS_Shape &, const Standard_Boolean, const Standard_Boolean)) &ShapeAnalysis_FreeBoundsProperties::Init, "Initializes the object with given parameters. <shape> should be a compound of shells.", py::arg("shape"), py::arg("splitclosed"), py::arg("splitopen"));
cls_ShapeAnalysis_FreeBoundsProperties.def("Perform", (Standard_Boolean (ShapeAnalysis_FreeBoundsProperties::*)()) &ShapeAnalysis_FreeBoundsProperties::Perform, "Builds and analyzes free bounds of the shape. First calls ShapeAnalysis_FreeBounds for building free bounds. Then on each free bound computes its properties: - area of the contour, - perimeter of the contour, - ratio of average length to average width of the contour, - average width of contour, - notches on the contour and for each notch - maximum width of the notch.");
cls_ShapeAnalysis_FreeBoundsProperties.def("IsLoaded", (Standard_Boolean (ShapeAnalysis_FreeBoundsProperties::*)() const) &ShapeAnalysis_FreeBoundsProperties::IsLoaded, "Returns True if shape is loaded");
cls_ShapeAnalysis_FreeBoundsProperties.def("Shape", (TopoDS_Shape (ShapeAnalysis_FreeBoundsProperties::*)() const) &ShapeAnalysis_FreeBoundsProperties::Shape, "Returns shape");
cls_ShapeAnalysis_FreeBoundsProperties.def("Tolerance", (Standard_Real (ShapeAnalysis_FreeBoundsProperties::*)() const) &ShapeAnalysis_FreeBoundsProperties::Tolerance, "Returns tolerance");
cls_ShapeAnalysis_FreeBoundsProperties.def("NbFreeBounds", (Standard_Integer (ShapeAnalysis_FreeBoundsProperties::*)() const) &ShapeAnalysis_FreeBoundsProperties::NbFreeBounds, "Returns number of free bounds");
cls_ShapeAnalysis_FreeBoundsProperties.def("NbClosedFreeBounds", (Standard_Integer (ShapeAnalysis_FreeBoundsProperties::*)() const) &ShapeAnalysis_FreeBoundsProperties::NbClosedFreeBounds, "Returns number of closed free bounds");
cls_ShapeAnalysis_FreeBoundsProperties.def("NbOpenFreeBounds", (Standard_Integer (ShapeAnalysis_FreeBoundsProperties::*)() const) &ShapeAnalysis_FreeBoundsProperties::NbOpenFreeBounds, "Returns number of open free bounds");
cls_ShapeAnalysis_FreeBoundsProperties.def("ClosedFreeBounds", (opencascade::handle<ShapeAnalysis_HSequenceOfFreeBounds> (ShapeAnalysis_FreeBoundsProperties::*)() const) &ShapeAnalysis_FreeBoundsProperties::ClosedFreeBounds, "Returns all closed free bounds");
cls_ShapeAnalysis_FreeBoundsProperties.def("OpenFreeBounds", (opencascade::handle<ShapeAnalysis_HSequenceOfFreeBounds> (ShapeAnalysis_FreeBoundsProperties::*)() const) &ShapeAnalysis_FreeBoundsProperties::OpenFreeBounds, "Returns all open free bounds");
cls_ShapeAnalysis_FreeBoundsProperties.def("ClosedFreeBound", (opencascade::handle<ShapeAnalysis_FreeBoundData> (ShapeAnalysis_FreeBoundsProperties::*)(const Standard_Integer) const) &ShapeAnalysis_FreeBoundsProperties::ClosedFreeBound, "Returns properties of closed free bound specified by its rank number", py::arg("index"));
cls_ShapeAnalysis_FreeBoundsProperties.def("OpenFreeBound", (opencascade::handle<ShapeAnalysis_FreeBoundData> (ShapeAnalysis_FreeBoundsProperties::*)(const Standard_Integer) const) &ShapeAnalysis_FreeBoundsProperties::OpenFreeBound, "Returns properties of open free bound specified by its rank number", py::arg("index"));
cls_ShapeAnalysis_FreeBoundsProperties.def("DispatchBounds", (Standard_Boolean (ShapeAnalysis_FreeBoundsProperties::*)()) &ShapeAnalysis_FreeBoundsProperties::DispatchBounds, "None");
cls_ShapeAnalysis_FreeBoundsProperties.def("CheckContours", [](ShapeAnalysis_FreeBoundsProperties &self) -> Standard_Boolean { return self.CheckContours(); });
cls_ShapeAnalysis_FreeBoundsProperties.def("CheckContours", (Standard_Boolean (ShapeAnalysis_FreeBoundsProperties::*)(const Standard_Real)) &ShapeAnalysis_FreeBoundsProperties::CheckContours, "None", py::arg("prec"));
cls_ShapeAnalysis_FreeBoundsProperties.def("CheckNotches", [](ShapeAnalysis_FreeBoundsProperties &self) -> Standard_Boolean { return self.CheckNotches(); });
cls_ShapeAnalysis_FreeBoundsProperties.def("CheckNotches", (Standard_Boolean (ShapeAnalysis_FreeBoundsProperties::*)(const Standard_Real)) &ShapeAnalysis_FreeBoundsProperties::CheckNotches, "None", py::arg("prec"));
cls_ShapeAnalysis_FreeBoundsProperties.def("CheckNotches", [](ShapeAnalysis_FreeBoundsProperties &self, opencascade::handle<ShapeAnalysis_FreeBoundData> & a0) -> Standard_Boolean { return self.CheckNotches(a0); });
cls_ShapeAnalysis_FreeBoundsProperties.def("CheckNotches", (Standard_Boolean (ShapeAnalysis_FreeBoundsProperties::*)(opencascade::handle<ShapeAnalysis_FreeBoundData> &, const Standard_Real)) &ShapeAnalysis_FreeBoundsProperties::CheckNotches, "None", py::arg("fbData"), py::arg("prec"));
cls_ShapeAnalysis_FreeBoundsProperties.def("CheckNotches", [](ShapeAnalysis_FreeBoundsProperties &self, const TopoDS_Wire & freebound, const Standard_Integer num, TopoDS_Wire & notch, Standard_Real & distMax, const Standard_Real prec){ Standard_Boolean rv = self.CheckNotches(freebound, num, notch, distMax, prec); return std::tuple<Standard_Boolean, Standard_Real &>(rv, distMax); }, "None", py::arg("freebound"), py::arg("num"), py::arg("notch"), py::arg("distMax"), py::arg("prec"));
cls_ShapeAnalysis_FreeBoundsProperties.def("FillProperties", [](ShapeAnalysis_FreeBoundsProperties &self, opencascade::handle<ShapeAnalysis_FreeBoundData> & a0) -> Standard_Boolean { return self.FillProperties(a0); });
cls_ShapeAnalysis_FreeBoundsProperties.def("FillProperties", (Standard_Boolean (ShapeAnalysis_FreeBoundsProperties::*)(opencascade::handle<ShapeAnalysis_FreeBoundData> &, const Standard_Real)) &ShapeAnalysis_FreeBoundsProperties::FillProperties, "None", py::arg("fbData"), py::arg("prec"));

// CLASS: SHAPEANALYSIS_GEOM
py::class_<ShapeAnalysis_Geom> cls_ShapeAnalysis_Geom(mod, "ShapeAnalysis_Geom", "Analyzing tool aimed to work on primitive geometrical objects");

// Methods
// cls_ShapeAnalysis_Geom.def_static("operator new_", (void * (*)(size_t)) &ShapeAnalysis_Geom::operator new, "None", py::arg("theSize"));
// cls_ShapeAnalysis_Geom.def_static("operator delete_", (void (*)(void *)) &ShapeAnalysis_Geom::operator delete, "None", py::arg("theAddress"));
// cls_ShapeAnalysis_Geom.def_static("operator new[]_", (void * (*)(size_t)) &ShapeAnalysis_Geom::operator new[], "None", py::arg("theSize"));
// cls_ShapeAnalysis_Geom.def_static("operator delete[]_", (void (*)(void *)) &ShapeAnalysis_Geom::operator delete[], "None", py::arg("theAddress"));
// cls_ShapeAnalysis_Geom.def_static("operator new_", (void * (*)(size_t, void *)) &ShapeAnalysis_Geom::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ShapeAnalysis_Geom.def_static("operator delete_", (void (*)(void *, void *)) &ShapeAnalysis_Geom::operator delete, "None", py::arg(""), py::arg(""));
cls_ShapeAnalysis_Geom.def_static("NearestPlane_", [](const TColgp_Array1OfPnt & Pnts, gp_Pln & aPln, Standard_Real & Dmax){ Standard_Boolean rv = ShapeAnalysis_Geom::NearestPlane(Pnts, aPln, Dmax); return std::tuple<Standard_Boolean, Standard_Real &>(rv, Dmax); }, "Builds a plane out of a set of points in array Returns in <dmax> the maximal distance between the produced plane and given points", py::arg("Pnts"), py::arg("aPln"), py::arg("Dmax"));
cls_ShapeAnalysis_Geom.def_static("PositionTrsf_", (Standard_Boolean (*)(const opencascade::handle<TColStd_HArray2OfReal> &, gp_Trsf &, const Standard_Real, const Standard_Real)) &ShapeAnalysis_Geom::PositionTrsf, "Builds transfromation object out of matrix. Matrix must be 3 x 4. Unit is used as multiplier.", py::arg("coefs"), py::arg("trsf"), py::arg("unit"), py::arg("prec"));

// CLASS: SHAPEANALYSIS_SHAPECONTENTS
py::class_<ShapeAnalysis_ShapeContents> cls_ShapeAnalysis_ShapeContents(mod, "ShapeAnalysis_ShapeContents", "Dumps shape contents");

// Constructors
cls_ShapeAnalysis_ShapeContents.def(py::init<>());

// Methods
// cls_ShapeAnalysis_ShapeContents.def_static("operator new_", (void * (*)(size_t)) &ShapeAnalysis_ShapeContents::operator new, "None", py::arg("theSize"));
// cls_ShapeAnalysis_ShapeContents.def_static("operator delete_", (void (*)(void *)) &ShapeAnalysis_ShapeContents::operator delete, "None", py::arg("theAddress"));
// cls_ShapeAnalysis_ShapeContents.def_static("operator new[]_", (void * (*)(size_t)) &ShapeAnalysis_ShapeContents::operator new[], "None", py::arg("theSize"));
// cls_ShapeAnalysis_ShapeContents.def_static("operator delete[]_", (void (*)(void *)) &ShapeAnalysis_ShapeContents::operator delete[], "None", py::arg("theAddress"));
// cls_ShapeAnalysis_ShapeContents.def_static("operator new_", (void * (*)(size_t, void *)) &ShapeAnalysis_ShapeContents::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ShapeAnalysis_ShapeContents.def_static("operator delete_", (void (*)(void *, void *)) &ShapeAnalysis_ShapeContents::operator delete, "None", py::arg(""), py::arg(""));
cls_ShapeAnalysis_ShapeContents.def("Clear", (void (ShapeAnalysis_ShapeContents::*)()) &ShapeAnalysis_ShapeContents::Clear, "Clears all accumulated statictics");
cls_ShapeAnalysis_ShapeContents.def("ClearFlags", (void (ShapeAnalysis_ShapeContents::*)()) &ShapeAnalysis_ShapeContents::ClearFlags, "Clears all flags");
cls_ShapeAnalysis_ShapeContents.def("Perform", (void (ShapeAnalysis_ShapeContents::*)(const TopoDS_Shape &)) &ShapeAnalysis_ShapeContents::Perform, "Counts quantities of sun-shapes in shape and stores sub-shapes according to flags", py::arg("shape"));
cls_ShapeAnalysis_ShapeContents.def("ModifyBigSplineMode", (Standard_Boolean & (ShapeAnalysis_ShapeContents::*)()) &ShapeAnalysis_ShapeContents::ModifyBigSplineMode, "Returns (modifiable) the flag which defines whether to store faces with edges if its 3D curves has more than 8192 poles.");
cls_ShapeAnalysis_ShapeContents.def("ModifyIndirectMode", (Standard_Boolean & (ShapeAnalysis_ShapeContents::*)()) &ShapeAnalysis_ShapeContents::ModifyIndirectMode, "Returns (modifiable) the flag which defines whether to store faces on indirect surfaces");
cls_ShapeAnalysis_ShapeContents.def("ModifyOffestSurfaceMode", (Standard_Boolean & (ShapeAnalysis_ShapeContents::*)()) &ShapeAnalysis_ShapeContents::ModifyOffestSurfaceMode, "Returns (modifiable) the flag which defines whether to store faces on offset surfaces.");
cls_ShapeAnalysis_ShapeContents.def("ModifyTrimmed3dMode", (Standard_Boolean & (ShapeAnalysis_ShapeContents::*)()) &ShapeAnalysis_ShapeContents::ModifyTrimmed3dMode, "Returns (modifiable) the flag which defines whether to store faces with edges if ist 3D curves are trimmed curves");
cls_ShapeAnalysis_ShapeContents.def("ModifyOffsetCurveMode", (Standard_Boolean & (ShapeAnalysis_ShapeContents::*)()) &ShapeAnalysis_ShapeContents::ModifyOffsetCurveMode, "Returns (modifiable) the flag which defines whether to store faces with edges if its 3D curves and pcurves are offest curves");
cls_ShapeAnalysis_ShapeContents.def("ModifyTrimmed2dMode", (Standard_Boolean & (ShapeAnalysis_ShapeContents::*)()) &ShapeAnalysis_ShapeContents::ModifyTrimmed2dMode, "Returns (modifiable) the flag which defines whether to store faces with edges if its pcurves are trimmed curves");
cls_ShapeAnalysis_ShapeContents.def("NbSolids", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbSolids, "None");
cls_ShapeAnalysis_ShapeContents.def("NbShells", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbShells, "None");
cls_ShapeAnalysis_ShapeContents.def("NbFaces", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbFaces, "None");
cls_ShapeAnalysis_ShapeContents.def("NbWires", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbWires, "None");
cls_ShapeAnalysis_ShapeContents.def("NbEdges", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbEdges, "None");
cls_ShapeAnalysis_ShapeContents.def("NbVertices", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbVertices, "None");
cls_ShapeAnalysis_ShapeContents.def("NbSolidsWithVoids", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbSolidsWithVoids, "None");
cls_ShapeAnalysis_ShapeContents.def("NbBigSplines", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbBigSplines, "None");
cls_ShapeAnalysis_ShapeContents.def("NbC0Surfaces", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbC0Surfaces, "None");
cls_ShapeAnalysis_ShapeContents.def("NbC0Curves", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbC0Curves, "None");
cls_ShapeAnalysis_ShapeContents.def("NbOffsetSurf", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbOffsetSurf, "None");
cls_ShapeAnalysis_ShapeContents.def("NbIndirectSurf", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbIndirectSurf, "None");
cls_ShapeAnalysis_ShapeContents.def("NbOffsetCurves", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbOffsetCurves, "None");
cls_ShapeAnalysis_ShapeContents.def("NbTrimmedCurve2d", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbTrimmedCurve2d, "None");
cls_ShapeAnalysis_ShapeContents.def("NbTrimmedCurve3d", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbTrimmedCurve3d, "None");
cls_ShapeAnalysis_ShapeContents.def("NbBSplibeSurf", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbBSplibeSurf, "None");
cls_ShapeAnalysis_ShapeContents.def("NbBezierSurf", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbBezierSurf, "None");
cls_ShapeAnalysis_ShapeContents.def("NbTrimSurf", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbTrimSurf, "None");
cls_ShapeAnalysis_ShapeContents.def("NbWireWitnSeam", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbWireWitnSeam, "None");
cls_ShapeAnalysis_ShapeContents.def("NbWireWithSevSeams", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbWireWithSevSeams, "None");
cls_ShapeAnalysis_ShapeContents.def("NbFaceWithSevWires", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbFaceWithSevWires, "None");
cls_ShapeAnalysis_ShapeContents.def("NbNoPCurve", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbNoPCurve, "None");
cls_ShapeAnalysis_ShapeContents.def("NbFreeFaces", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbFreeFaces, "None");
cls_ShapeAnalysis_ShapeContents.def("NbFreeWires", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbFreeWires, "None");
cls_ShapeAnalysis_ShapeContents.def("NbFreeEdges", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbFreeEdges, "None");
cls_ShapeAnalysis_ShapeContents.def("NbSharedSolids", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbSharedSolids, "None");
cls_ShapeAnalysis_ShapeContents.def("NbSharedShells", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbSharedShells, "None");
cls_ShapeAnalysis_ShapeContents.def("NbSharedFaces", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbSharedFaces, "None");
cls_ShapeAnalysis_ShapeContents.def("NbSharedWires", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbSharedWires, "None");
cls_ShapeAnalysis_ShapeContents.def("NbSharedFreeWires", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbSharedFreeWires, "None");
cls_ShapeAnalysis_ShapeContents.def("NbSharedFreeEdges", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbSharedFreeEdges, "None");
cls_ShapeAnalysis_ShapeContents.def("NbSharedEdges", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbSharedEdges, "None");
cls_ShapeAnalysis_ShapeContents.def("NbSharedVertices", (Standard_Integer (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::NbSharedVertices, "None");
cls_ShapeAnalysis_ShapeContents.def("BigSplineSec", (opencascade::handle<TopTools_HSequenceOfShape> (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::BigSplineSec, "None");
cls_ShapeAnalysis_ShapeContents.def("IndirectSec", (opencascade::handle<TopTools_HSequenceOfShape> (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::IndirectSec, "None");
cls_ShapeAnalysis_ShapeContents.def("OffsetSurfaceSec", (opencascade::handle<TopTools_HSequenceOfShape> (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::OffsetSurfaceSec, "None");
cls_ShapeAnalysis_ShapeContents.def("Trimmed3dSec", (opencascade::handle<TopTools_HSequenceOfShape> (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::Trimmed3dSec, "None");
cls_ShapeAnalysis_ShapeContents.def("OffsetCurveSec", (opencascade::handle<TopTools_HSequenceOfShape> (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::OffsetCurveSec, "None");
cls_ShapeAnalysis_ShapeContents.def("Trimmed2dSec", (opencascade::handle<TopTools_HSequenceOfShape> (ShapeAnalysis_ShapeContents::*)() const) &ShapeAnalysis_ShapeContents::Trimmed2dSec, "None");

// CLASS: SHAPEANALYSIS_SHAPETOLERANCE
py::class_<ShapeAnalysis_ShapeTolerance> cls_ShapeAnalysis_ShapeTolerance(mod, "ShapeAnalysis_ShapeTolerance", "Tool for computing shape tolerances (minimal, maximal, average), finding shape with tolerance matching given criteria, setting or limitating tolerances.");

// Constructors
cls_ShapeAnalysis_ShapeTolerance.def(py::init<>());

// Methods
// cls_ShapeAnalysis_ShapeTolerance.def_static("operator new_", (void * (*)(size_t)) &ShapeAnalysis_ShapeTolerance::operator new, "None", py::arg("theSize"));
// cls_ShapeAnalysis_ShapeTolerance.def_static("operator delete_", (void (*)(void *)) &ShapeAnalysis_ShapeTolerance::operator delete, "None", py::arg("theAddress"));
// cls_ShapeAnalysis_ShapeTolerance.def_static("operator new[]_", (void * (*)(size_t)) &ShapeAnalysis_ShapeTolerance::operator new[], "None", py::arg("theSize"));
// cls_ShapeAnalysis_ShapeTolerance.def_static("operator delete[]_", (void (*)(void *)) &ShapeAnalysis_ShapeTolerance::operator delete[], "None", py::arg("theAddress"));
// cls_ShapeAnalysis_ShapeTolerance.def_static("operator new_", (void * (*)(size_t, void *)) &ShapeAnalysis_ShapeTolerance::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ShapeAnalysis_ShapeTolerance.def_static("operator delete_", (void (*)(void *, void *)) &ShapeAnalysis_ShapeTolerance::operator delete, "None", py::arg(""), py::arg(""));
cls_ShapeAnalysis_ShapeTolerance.def("Tolerance", [](ShapeAnalysis_ShapeTolerance &self, const TopoDS_Shape & a0, const Standard_Integer a1) -> Standard_Real { return self.Tolerance(a0, a1); });
cls_ShapeAnalysis_ShapeTolerance.def("Tolerance", (Standard_Real (ShapeAnalysis_ShapeTolerance::*)(const TopoDS_Shape &, const Standard_Integer, const TopAbs_ShapeEnum)) &ShapeAnalysis_ShapeTolerance::Tolerance, "Determines a tolerance from the ones stored in a shape Remark : calls InitTolerance and AddTolerance, hence, can be used to start a series for cumulating tolerance <mode> = 0 : returns the average value between sub-shapes, <mode> > 0 : returns the maximal found, <mode> < 0 : returns the minimal found. <type> defines what kinds of sub-shapes to consider: SHAPE (default) : all : VERTEX, EDGE, FACE, VERTEX : only vertices, EDGE : only edges, FACE : only faces, SHELL : combined SHELL + FACE, for each face (and containing shell), also checks EDGE and VERTEX", py::arg("shape"), py::arg("mode"), py::arg("type"));
cls_ShapeAnalysis_ShapeTolerance.def("OverTolerance", [](ShapeAnalysis_ShapeTolerance &self, const TopoDS_Shape & a0, const Standard_Real a1) -> opencascade::handle<TopTools_HSequenceOfShape> { return self.OverTolerance(a0, a1); });
cls_ShapeAnalysis_ShapeTolerance.def("OverTolerance", (opencascade::handle<TopTools_HSequenceOfShape> (ShapeAnalysis_ShapeTolerance::*)(const TopoDS_Shape &, const Standard_Real, const TopAbs_ShapeEnum) const) &ShapeAnalysis_ShapeTolerance::OverTolerance, "Determines which shapes have a tolerance over the given value <type> is interpreted as in the method Tolerance", py::arg("shape"), py::arg("value"), py::arg("type"));
cls_ShapeAnalysis_ShapeTolerance.def("InTolerance", [](ShapeAnalysis_ShapeTolerance &self, const TopoDS_Shape & a0, const Standard_Real a1, const Standard_Real a2) -> opencascade::handle<TopTools_HSequenceOfShape> { return self.InTolerance(a0, a1, a2); });
cls_ShapeAnalysis_ShapeTolerance.def("InTolerance", (opencascade::handle<TopTools_HSequenceOfShape> (ShapeAnalysis_ShapeTolerance::*)(const TopoDS_Shape &, const Standard_Real, const Standard_Real, const TopAbs_ShapeEnum) const) &ShapeAnalysis_ShapeTolerance::InTolerance, "Determines which shapes have a tolerance within a given interval <type> is interpreted as in the method Tolerance", py::arg("shape"), py::arg("valmin"), py::arg("valmax"), py::arg("type"));
cls_ShapeAnalysis_ShapeTolerance.def("InitTolerance", (void (ShapeAnalysis_ShapeTolerance::*)()) &ShapeAnalysis_ShapeTolerance::InitTolerance, "Initializes computation of cumulated tolerance");
cls_ShapeAnalysis_ShapeTolerance.def("AddTolerance", [](ShapeAnalysis_ShapeTolerance &self, const TopoDS_Shape & a0) -> void { return self.AddTolerance(a0); });
cls_ShapeAnalysis_ShapeTolerance.def("AddTolerance", (void (ShapeAnalysis_ShapeTolerance::*)(const TopoDS_Shape &, const TopAbs_ShapeEnum)) &ShapeAnalysis_ShapeTolerance::AddTolerance, "Adds data on new Shape to compute Cumulated Tolerance (prepares three computations : maximal, average, minimal)", py::arg("shape"), py::arg("type"));
cls_ShapeAnalysis_ShapeTolerance.def("GlobalTolerance", (Standard_Real (ShapeAnalysis_ShapeTolerance::*)(const Standard_Integer) const) &ShapeAnalysis_ShapeTolerance::GlobalTolerance, "Returns the computed tolerance according to the <mode> <mode> = 0 : average <mode> > 0 : maximal <mode> < 0 : minimal", py::arg("mode"));

// CLASS: SHAPEANALYSIS_SHELL
py::class_<ShapeAnalysis_Shell> cls_ShapeAnalysis_Shell(mod, "ShapeAnalysis_Shell", "This class provides operators to analyze edges orientation in the shell.");

// Methods
// cls_ShapeAnalysis_Shell.def_static("operator new_", (void * (*)(size_t)) &ShapeAnalysis_Shell::operator new, "None", py::arg("theSize"));
// cls_ShapeAnalysis_Shell.def_static("operator delete_", (void (*)(void *)) &ShapeAnalysis_Shell::operator delete, "None", py::arg("theAddress"));
// cls_ShapeAnalysis_Shell.def_static("operator new[]_", (void * (*)(size_t)) &ShapeAnalysis_Shell::operator new[], "None", py::arg("theSize"));
// cls_ShapeAnalysis_Shell.def_static("operator delete[]_", (void (*)(void *)) &ShapeAnalysis_Shell::operator delete[], "None", py::arg("theAddress"));
// cls_ShapeAnalysis_Shell.def_static("operator new_", (void * (*)(size_t, void *)) &ShapeAnalysis_Shell::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ShapeAnalysis_Shell.def_static("operator delete_", (void (*)(void *, void *)) &ShapeAnalysis_Shell::operator delete, "None", py::arg(""), py::arg(""));
cls_ShapeAnalysis_Shell.def("Clear", (void (ShapeAnalysis_Shell::*)()) &ShapeAnalysis_Shell::Clear, "Clears data about loaded shells and performed checks");
cls_ShapeAnalysis_Shell.def("LoadShells", (void (ShapeAnalysis_Shell::*)(const TopoDS_Shape &)) &ShapeAnalysis_Shell::LoadShells, "Adds shells contained in the <shape> to the list of loaded shells", py::arg("shape"));
cls_ShapeAnalysis_Shell.def("CheckOrientedShells", [](ShapeAnalysis_Shell &self, const TopoDS_Shape & a0) -> Standard_Boolean { return self.CheckOrientedShells(a0); });
cls_ShapeAnalysis_Shell.def("CheckOrientedShells", [](ShapeAnalysis_Shell &self, const TopoDS_Shape & a0, const Standard_Boolean a1) -> Standard_Boolean { return self.CheckOrientedShells(a0, a1); });
cls_ShapeAnalysis_Shell.def("CheckOrientedShells", (Standard_Boolean (ShapeAnalysis_Shell::*)(const TopoDS_Shape &, const Standard_Boolean, const Standard_Boolean)) &ShapeAnalysis_Shell::CheckOrientedShells, "Checks if shells fulfill orientation condition, i.e. if each edge is, either present once (free edge) or twice (connected edge) but with different orientations (FORWARD/REVERSED) Edges which do not fulfill these conditions are bad", py::arg("shape"), py::arg("alsofree"), py::arg("checkinternaledges"));
cls_ShapeAnalysis_Shell.def("IsLoaded", (Standard_Boolean (ShapeAnalysis_Shell::*)(const TopoDS_Shape &) const) &ShapeAnalysis_Shell::IsLoaded, "Tells if a shape is loaded (only shells are checked)", py::arg("shape"));
cls_ShapeAnalysis_Shell.def("NbLoaded", (Standard_Integer (ShapeAnalysis_Shell::*)() const) &ShapeAnalysis_Shell::NbLoaded, "Returns the actual number of loaded shapes (i.e. shells)");
cls_ShapeAnalysis_Shell.def("Loaded", (TopoDS_Shape (ShapeAnalysis_Shell::*)(const Standard_Integer) const) &ShapeAnalysis_Shell::Loaded, "Returns a loaded shape specified by its rank number. Returns null shape if <num> is out of range", py::arg("num"));
cls_ShapeAnalysis_Shell.def("HasBadEdges", (Standard_Boolean (ShapeAnalysis_Shell::*)() const) &ShapeAnalysis_Shell::HasBadEdges, "Tells if at least one edge is recorded as bad");
cls_ShapeAnalysis_Shell.def("BadEdges", (TopoDS_Compound (ShapeAnalysis_Shell::*)() const) &ShapeAnalysis_Shell::BadEdges, "Returns the list of bad edges as a Compound It is empty (not null) if no edge are recorded as bad");
cls_ShapeAnalysis_Shell.def("HasFreeEdges", (Standard_Boolean (ShapeAnalysis_Shell::*)() const) &ShapeAnalysis_Shell::HasFreeEdges, "Tells if at least one edge is recorded as free (not connected)");
cls_ShapeAnalysis_Shell.def("FreeEdges", (TopoDS_Compound (ShapeAnalysis_Shell::*)() const) &ShapeAnalysis_Shell::FreeEdges, "Returns the list of free (not connected) edges as a Compound It is empty (not null) if no edge are recorded as free");
cls_ShapeAnalysis_Shell.def("HasConnectedEdges", (Standard_Boolean (ShapeAnalysis_Shell::*)() const) &ShapeAnalysis_Shell::HasConnectedEdges, "Tells if at least one edge is connected (shared twice or more)");

// CLASS: SHAPEANALYSIS_SURFACE
py::class_<ShapeAnalysis_Surface, opencascade::handle<ShapeAnalysis_Surface>, Standard_Transient> cls_ShapeAnalysis_Surface(mod, "ShapeAnalysis_Surface", "Complements standard tool Geom_Surface by providing additional functionality for detection surface singularities, checking spatial surface closure and computing projections of 3D points onto a surface.");

// Constructors
cls_ShapeAnalysis_Surface.def(py::init<const opencascade::handle<Geom_Surface> &>(), py::arg("S"));

// Methods
cls_ShapeAnalysis_Surface.def("Init", (void (ShapeAnalysis_Surface::*)(const opencascade::handle<Geom_Surface> &)) &ShapeAnalysis_Surface::Init, "Loads existing surface", py::arg("S"));
cls_ShapeAnalysis_Surface.def("Init", (void (ShapeAnalysis_Surface::*)(const opencascade::handle<ShapeAnalysis_Surface> &)) &ShapeAnalysis_Surface::Init, "Reads all the data from another Surface, without recomputing", py::arg("other"));
cls_ShapeAnalysis_Surface.def("SetDomain", (void (ShapeAnalysis_Surface::*)(const Standard_Real, const Standard_Real, const Standard_Real, const Standard_Real)) &ShapeAnalysis_Surface::SetDomain, "None", py::arg("U1"), py::arg("U2"), py::arg("V1"), py::arg("V2"));
cls_ShapeAnalysis_Surface.def("Surface", (const opencascade::handle<Geom_Surface> & (ShapeAnalysis_Surface::*)() const) &ShapeAnalysis_Surface::Surface, "Returns a surface being analyzed");
cls_ShapeAnalysis_Surface.def("Adaptor3d", (const opencascade::handle<GeomAdaptor_HSurface> & (ShapeAnalysis_Surface::*)()) &ShapeAnalysis_Surface::Adaptor3d, "Returns the Adaptor. Creates it if not yet done.");
cls_ShapeAnalysis_Surface.def("TrueAdaptor3d", (const opencascade::handle<GeomAdaptor_HSurface> & (ShapeAnalysis_Surface::*)() const) &ShapeAnalysis_Surface::TrueAdaptor3d, "Returns the Adaptor (may be Null if method Adaptor() was not called)");
cls_ShapeAnalysis_Surface.def("Gap", (Standard_Real (ShapeAnalysis_Surface::*)() const) &ShapeAnalysis_Surface::Gap, "Returns 3D distance found by one of the following methods. IsDegenerated, DegeneratedValues, ProjectDegenerated (distance between 3D point and found or last (if not found) singularity), IsUClosed, IsVClosed (minimum value of precision to consider the surface to be closed), ValueOfUV (distance between 3D point and found solution).");
cls_ShapeAnalysis_Surface.def("Value", (gp_Pnt (ShapeAnalysis_Surface::*)(const Standard_Real, const Standard_Real)) &ShapeAnalysis_Surface::Value, "Returns a 3D point specified by parameters in surface parametrical space", py::arg("u"), py::arg("v"));
cls_ShapeAnalysis_Surface.def("Value", (gp_Pnt (ShapeAnalysis_Surface::*)(const gp_Pnt2d &)) &ShapeAnalysis_Surface::Value, "Returns a 3d point specified by a point in surface parametrical space", py::arg("p2d"));
cls_ShapeAnalysis_Surface.def("HasSingularities", (Standard_Boolean (ShapeAnalysis_Surface::*)(const Standard_Real)) &ShapeAnalysis_Surface::HasSingularities, "Returns True if the surface has singularities for the given precision (i.e. if there are surface singularities with sizes not greater than precision).", py::arg("preci"));
cls_ShapeAnalysis_Surface.def("NbSingularities", (Standard_Integer (ShapeAnalysis_Surface::*)(const Standard_Real)) &ShapeAnalysis_Surface::NbSingularities, "Returns the number of singularities for the given precision (i.e. number of surface singularities with sizes not greater than precision).", py::arg("preci"));
cls_ShapeAnalysis_Surface.def("Singularity", [](ShapeAnalysis_Surface &self, const Standard_Integer num, Standard_Real & preci, gp_Pnt & P3d, gp_Pnt2d & firstP2d, gp_Pnt2d & lastP2d, Standard_Real & firstpar, Standard_Real & lastpar, Standard_Boolean & uisodeg){ Standard_Boolean rv = self.Singularity(num, preci, P3d, firstP2d, lastP2d, firstpar, lastpar, uisodeg); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &, Standard_Real &, Standard_Boolean &>(rv, preci, firstpar, lastpar, uisodeg); }, "Returns the characteristics of the singularity specified by its rank number <num>. That means, that it is not neccessary for <num> to be in the range [1, NbSingularities] but must be not greater than possible (see ComputeSingularities). The returned characteristics are: preci: the smallest precision with which the iso-line is considered as degenerated, P3d: 3D point of singularity (middle point of the surface iso-line), firstP2d and lastP2d: first and last 2D points of the iso-line in parametrical surface, firstpar and lastpar: first and last parameters of the iso-line in parametrical surface, uisodeg: if the degenerated iso-line is U-iso (True) or V-iso (False). Returns False if <num> is out of range, else returns True.", py::arg("num"), py::arg("preci"), py::arg("P3d"), py::arg("firstP2d"), py::arg("lastP2d"), py::arg("firstpar"), py::arg("lastpar"), py::arg("uisodeg"));
cls_ShapeAnalysis_Surface.def("IsDegenerated", (Standard_Boolean (ShapeAnalysis_Surface::*)(const gp_Pnt &, const Standard_Real)) &ShapeAnalysis_Surface::IsDegenerated, "Returns True if there is at least one surface boundary which is considered as degenerated with <preci> and distance between P3d and corresponding singular point is less than <preci>", py::arg("P3d"), py::arg("preci"));
cls_ShapeAnalysis_Surface.def("DegeneratedValues", [](ShapeAnalysis_Surface &self, const gp_Pnt & P3d, const Standard_Real preci, gp_Pnt2d & firstP2d, gp_Pnt2d & lastP2d, Standard_Real & firstpar, Standard_Real & lastpar, const Standard_Boolean forward){ Standard_Boolean rv = self.DegeneratedValues(P3d, preci, firstP2d, lastP2d, firstpar, lastpar, forward); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &>(rv, firstpar, lastpar); }, "Returns True if there is at least one surface iso-line which is considered as degenerated with <preci> and distance between P3d and corresponding singular point is less than <preci> (like IsDegenerated). Returns characteristics of the first found boundary matching those criteria.", py::arg("P3d"), py::arg("preci"), py::arg("firstP2d"), py::arg("lastP2d"), py::arg("firstpar"), py::arg("lastpar"), py::arg("forward"));
cls_ShapeAnalysis_Surface.def("ProjectDegenerated", (Standard_Boolean (ShapeAnalysis_Surface::*)(const gp_Pnt &, const Standard_Real, const gp_Pnt2d &, gp_Pnt2d &)) &ShapeAnalysis_Surface::ProjectDegenerated, "Projects a point <P3d> on a singularity by computing one of the coordinates of preliminary computed <result>.", py::arg("P3d"), py::arg("preci"), py::arg("neighbour"), py::arg("result"));
cls_ShapeAnalysis_Surface.def("ProjectDegenerated", (Standard_Boolean (ShapeAnalysis_Surface::*)(const Standard_Integer, const TColgp_SequenceOfPnt &, TColgp_SequenceOfPnt2d &, const Standard_Real, const Standard_Boolean)) &ShapeAnalysis_Surface::ProjectDegenerated, "Checks points at the beginning (direct is True) or end (direct is False) of array <points> to lie in singularity of surface, and if yes, adjusts the indeterminate 2d coordinate of these points by nearest point which is not in singularity. Returns True if some points were adjusted.", py::arg("nbrPnt"), py::arg("points"), py::arg("pnt2d"), py::arg("preci"), py::arg("direct"));
cls_ShapeAnalysis_Surface.def("IsDegenerated", (Standard_Boolean (ShapeAnalysis_Surface::*)(const gp_Pnt2d &, const gp_Pnt2d &, const Standard_Real, const Standard_Real)) &ShapeAnalysis_Surface::IsDegenerated, "Returns True if straight pcurve going from point p2d1 to p2d2 is degenerate, i.e. lies in the singularity of the surface. NOTE: it uses another method of detecting singularity than used by ComputeSingularities() et al.! For that, maximums of distances between points p2d1, p2d2 and 0.5*(p2d1+p2d2) and between corresponding 3d points are computed. The pcurve (p2d1, p2d2) is considered as degenerate if: - max distance in 3d is less than <tol> - max distance in 2d is at least <ratio> times greather than the Resolution computed from max distance in 3d (max3d < tol && max2d > ratio * Resolution(max3d)) NOTE: <ratio> should be >1 (e.g. 10)", py::arg("p2d1"), py::arg("p2d2"), py::arg("tol"), py::arg("ratio"));
cls_ShapeAnalysis_Surface.def("Bounds", [](ShapeAnalysis_Surface &self, Standard_Real & ufirst, Standard_Real & ulast, Standard_Real & vfirst, Standard_Real & vlast){ self.Bounds(ufirst, ulast, vfirst, vlast); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &>(ufirst, ulast, vfirst, vlast); }, "Returns the bounds of the surface (from Bounds from Surface, but buffered)", py::arg("ufirst"), py::arg("ulast"), py::arg("vfirst"), py::arg("vlast"));
cls_ShapeAnalysis_Surface.def("ComputeBoundIsos", (void (ShapeAnalysis_Surface::*)()) &ShapeAnalysis_Surface::ComputeBoundIsos, "Computes bound isos (protected against exceptions)");
cls_ShapeAnalysis_Surface.def("UIso", (opencascade::handle<Geom_Curve> (ShapeAnalysis_Surface::*)(const Standard_Real)) &ShapeAnalysis_Surface::UIso, "Returns a U-Iso. Null if not possible or failed Remark : bound isos are buffered", py::arg("U"));
cls_ShapeAnalysis_Surface.def("VIso", (opencascade::handle<Geom_Curve> (ShapeAnalysis_Surface::*)(const Standard_Real)) &ShapeAnalysis_Surface::VIso, "Returns a V-Iso. Null if not possible or failed Remark : bound isos are buffered", py::arg("V"));
cls_ShapeAnalysis_Surface.def("IsUClosed", [](ShapeAnalysis_Surface &self) -> Standard_Boolean { return self.IsUClosed(); });
cls_ShapeAnalysis_Surface.def("IsUClosed", (Standard_Boolean (ShapeAnalysis_Surface::*)(const Standard_Real)) &ShapeAnalysis_Surface::IsUClosed, "Tells if the Surface is spatially closed in U with given precision. If <preci> < 0 then Precision::Confusion is used. If Geom_Surface says that the surface is U-closed, this method also says this. Otherwise additional analysis is performed, comparing given precision with the following distances: - periodic B-Splines are closed, - polinomial B-Spline with boundary multiplicities degree+1 and Bezier - maximum distance between poles, - rational B-Spline or one with boundary multiplicities not degree+1 - maximum distance computed at knots and their middles, - surface of extrusion - distance between ends of basis curve, - other (RectangularTrimmed and Offset) - maximum distance computed at 100 equi-distanted points.", py::arg("preci"));
cls_ShapeAnalysis_Surface.def("IsVClosed", [](ShapeAnalysis_Surface &self) -> Standard_Boolean { return self.IsVClosed(); });
cls_ShapeAnalysis_Surface.def("IsVClosed", (Standard_Boolean (ShapeAnalysis_Surface::*)(const Standard_Real)) &ShapeAnalysis_Surface::IsVClosed, "Tells if the Surface is spatially closed in V with given precision. If <preci> < 0 then Precision::Confusion is used. If Geom_Surface says that the surface is V-closed, this method also says this. Otherwise additional analysis is performed, comparing given precision with the following distances: - periodic B-Splines are closed, - polinomial B-Spline with boundary multiplicities degree+1 and Bezier - maximum distance between poles, - rational B-Spline or one with boundary multiplicities not degree+1 - maximum distance computed at knots and their middles, - surface of revolution - distance between ends of basis curve, - other (RectangularTrimmed and Offset) - maximum distance computed at 100 equi-distanted points.", py::arg("preci"));
cls_ShapeAnalysis_Surface.def("ValueOfUV", (gp_Pnt2d (ShapeAnalysis_Surface::*)(const gp_Pnt &, const Standard_Real)) &ShapeAnalysis_Surface::ValueOfUV, "Computes the parameters in the surface parametrical space of 3D point. The result is parameters of the point projected onto the surface. This method enhances functionality provided by the standard tool GeomAPI_ProjectPointOnSurface by treatment of cases when the projected point is near to the surface boundaries and when this standard tool fails.", py::arg("P3D"), py::arg("preci"));
cls_ShapeAnalysis_Surface.def("NextValueOfUV", [](ShapeAnalysis_Surface &self, const gp_Pnt2d & a0, const gp_Pnt & a1, const Standard_Real a2) -> gp_Pnt2d { return self.NextValueOfUV(a0, a1, a2); });
cls_ShapeAnalysis_Surface.def("NextValueOfUV", (gp_Pnt2d (ShapeAnalysis_Surface::*)(const gp_Pnt2d &, const gp_Pnt &, const Standard_Real, const Standard_Real)) &ShapeAnalysis_Surface::NextValueOfUV, "Projects a point P3D on the surface. Does the same thing as ValueOfUV but tries to optimize computations by taking into account previous point <p2dPrev>: makes a step by UV and tries Newton algorithm. If <maxpreci> >0. and distance between solution and P3D is greater than <maxpreci>, that solution is considered as bad, and ValueOfUV() is used. If not succeded, calls ValueOfUV()", py::arg("p2dPrev"), py::arg("P3D"), py::arg("preci"), py::arg("maxpreci"));
cls_ShapeAnalysis_Surface.def("UVFromIso", [](ShapeAnalysis_Surface &self, const gp_Pnt & P3D, const Standard_Real preci, Standard_Real & U, Standard_Real & V){ Standard_Real rv = self.UVFromIso(P3D, preci, U, V); return std::tuple<Standard_Real, Standard_Real &, Standard_Real &>(rv, U, V); }, "Tries a refinement of an already computed couple (U,V) by using projecting 3D point on iso-lines: 1. boundaries of the surface, 2. iso-lines passing through (U,V) 3. iteratively received iso-lines passing through new U and new V (number of iterations is limited by 5 in each direction) Returns the best resulting distance between P3D and Value(U,V) in the case of success. Else, returns a very great value", py::arg("P3D"), py::arg("preci"), py::arg("U"), py::arg("V"));
cls_ShapeAnalysis_Surface.def("UCloseVal", (Standard_Real (ShapeAnalysis_Surface::*)() const) &ShapeAnalysis_Surface::UCloseVal, "Returns minimum value to consider the surface as U-closed");
cls_ShapeAnalysis_Surface.def("VCloseVal", (Standard_Real (ShapeAnalysis_Surface::*)() const) &ShapeAnalysis_Surface::VCloseVal, "Returns minimum value to consider the surface as V-closed");
cls_ShapeAnalysis_Surface.def("GetBoxUF", (const Bnd_Box & (ShapeAnalysis_Surface::*)()) &ShapeAnalysis_Surface::GetBoxUF, "None");
cls_ShapeAnalysis_Surface.def("GetBoxUL", (const Bnd_Box & (ShapeAnalysis_Surface::*)()) &ShapeAnalysis_Surface::GetBoxUL, "None");
cls_ShapeAnalysis_Surface.def("GetBoxVF", (const Bnd_Box & (ShapeAnalysis_Surface::*)()) &ShapeAnalysis_Surface::GetBoxVF, "None");
cls_ShapeAnalysis_Surface.def("GetBoxVL", (const Bnd_Box & (ShapeAnalysis_Surface::*)()) &ShapeAnalysis_Surface::GetBoxVL, "None");
cls_ShapeAnalysis_Surface.def_static("get_type_name_", (const char * (*)()) &ShapeAnalysis_Surface::get_type_name, "None");
cls_ShapeAnalysis_Surface.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &ShapeAnalysis_Surface::get_type_descriptor, "None");
cls_ShapeAnalysis_Surface.def("DynamicType", (const opencascade::handle<Standard_Type> & (ShapeAnalysis_Surface::*)() const) &ShapeAnalysis_Surface::DynamicType, "None");

// CLASS: SHAPEANALYSIS_TRANSFERPARAMETERS
py::class_<ShapeAnalysis_TransferParameters, opencascade::handle<ShapeAnalysis_TransferParameters>, Standard_Transient> cls_ShapeAnalysis_TransferParameters(mod, "ShapeAnalysis_TransferParameters", "This tool is used for transferring parameters from 3d curve of the edge to pcurve and vice versa.");

// Constructors
cls_ShapeAnalysis_TransferParameters.def(py::init<>());
cls_ShapeAnalysis_TransferParameters.def(py::init<const TopoDS_Edge &, const TopoDS_Face &>(), py::arg("E"), py::arg("F"));

// Methods
cls_ShapeAnalysis_TransferParameters.def("Init", (void (ShapeAnalysis_TransferParameters::*)(const TopoDS_Edge &, const TopoDS_Face &)) &ShapeAnalysis_TransferParameters::Init, "Initialize a tool with edge and face", py::arg("E"), py::arg("F"));
cls_ShapeAnalysis_TransferParameters.def("SetMaxTolerance", (void (ShapeAnalysis_TransferParameters::*)(const Standard_Real)) &ShapeAnalysis_TransferParameters::SetMaxTolerance, "Sets maximal tolerance to use linear recomputation of parameters.", py::arg("maxtol"));
cls_ShapeAnalysis_TransferParameters.def("Perform", (opencascade::handle<TColStd_HSequenceOfReal> (ShapeAnalysis_TransferParameters::*)(const opencascade::handle<TColStd_HSequenceOfReal> &, const Standard_Boolean)) &ShapeAnalysis_TransferParameters::Perform, "Transfers parameters given by sequence Params from 3d curve to pcurve (if To2d is True) or back (if To2d is False)", py::arg("Params"), py::arg("To2d"));
cls_ShapeAnalysis_TransferParameters.def("Perform", (Standard_Real (ShapeAnalysis_TransferParameters::*)(const Standard_Real, const Standard_Boolean)) &ShapeAnalysis_TransferParameters::Perform, "Transfers parameter given by sequence Params from 3d curve to pcurve (if To2d is True) or back (if To2d is False)", py::arg("Param"), py::arg("To2d"));
cls_ShapeAnalysis_TransferParameters.def("TransferRange", (void (ShapeAnalysis_TransferParameters::*)(TopoDS_Edge &, const Standard_Real, const Standard_Real, const Standard_Boolean)) &ShapeAnalysis_TransferParameters::TransferRange, "Recomputes range of curves from NewEdge. If Is2d equals True parameters are recomputed by curve2d else by curve3d.", py::arg("newEdge"), py::arg("prevPar"), py::arg("currPar"), py::arg("To2d"));
cls_ShapeAnalysis_TransferParameters.def("IsSameRange", (Standard_Boolean (ShapeAnalysis_TransferParameters::*)() const) &ShapeAnalysis_TransferParameters::IsSameRange, "Returns True if 3d curve of edge and pcurve are SameRange (in default implementation, if myScale == 1 and myShift == 0)");
cls_ShapeAnalysis_TransferParameters.def_static("get_type_name_", (const char * (*)()) &ShapeAnalysis_TransferParameters::get_type_name, "None");
cls_ShapeAnalysis_TransferParameters.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &ShapeAnalysis_TransferParameters::get_type_descriptor, "None");
cls_ShapeAnalysis_TransferParameters.def("DynamicType", (const opencascade::handle<Standard_Type> & (ShapeAnalysis_TransferParameters::*)() const) &ShapeAnalysis_TransferParameters::DynamicType, "None");

// CLASS: SHAPEANALYSIS_TRANSFERPARAMETERSPROJ
py::class_<ShapeAnalysis_TransferParametersProj, opencascade::handle<ShapeAnalysis_TransferParametersProj>, ShapeAnalysis_TransferParameters> cls_ShapeAnalysis_TransferParametersProj(mod, "ShapeAnalysis_TransferParametersProj", "This tool is used for transferring parameters from 3d curve of the edge to pcurve and vice versa. This tool transfers parameters with help of projection points from curve 3d on curve 2d and vice versa");

// Constructors
cls_ShapeAnalysis_TransferParametersProj.def(py::init<>());
cls_ShapeAnalysis_TransferParametersProj.def(py::init<const TopoDS_Edge &, const TopoDS_Face &>(), py::arg("E"), py::arg("F"));

// Methods
cls_ShapeAnalysis_TransferParametersProj.def("Init", (void (ShapeAnalysis_TransferParametersProj::*)(const TopoDS_Edge &, const TopoDS_Face &)) &ShapeAnalysis_TransferParametersProj::Init, "None", py::arg("E"), py::arg("F"));
cls_ShapeAnalysis_TransferParametersProj.def("Perform", (opencascade::handle<TColStd_HSequenceOfReal> (ShapeAnalysis_TransferParametersProj::*)(const opencascade::handle<TColStd_HSequenceOfReal> &, const Standard_Boolean)) &ShapeAnalysis_TransferParametersProj::Perform, "Transfers parameters given by sequence Params from 3d curve to pcurve (if To2d is True) or back (if To2d is False)", py::arg("Papams"), py::arg("To2d"));
cls_ShapeAnalysis_TransferParametersProj.def("Perform", (Standard_Real (ShapeAnalysis_TransferParametersProj::*)(const Standard_Real, const Standard_Boolean)) &ShapeAnalysis_TransferParametersProj::Perform, "Transfers parameter given by Param from 3d curve to pcurve (if To2d is True) or back (if To2d is False)", py::arg("Param"), py::arg("To2d"));
cls_ShapeAnalysis_TransferParametersProj.def("ForceProjection", (Standard_Boolean & (ShapeAnalysis_TransferParametersProj::*)()) &ShapeAnalysis_TransferParametersProj::ForceProjection, "Returns modifiable flag forcing projection If it is False (default), projection is done only if edge is not SameParameter or if tolerance of edge is greater than MaxTolerance()");
cls_ShapeAnalysis_TransferParametersProj.def("TransferRange", (void (ShapeAnalysis_TransferParametersProj::*)(TopoDS_Edge &, const Standard_Real, const Standard_Real, const Standard_Boolean)) &ShapeAnalysis_TransferParametersProj::TransferRange, "Recomputes range of curves from NewEdge. If Is2d equals True parameters are recomputed by curve2d else by curve3d.", py::arg("newEdge"), py::arg("prevPar"), py::arg("currPar"), py::arg("Is2d"));
cls_ShapeAnalysis_TransferParametersProj.def("IsSameRange", (Standard_Boolean (ShapeAnalysis_TransferParametersProj::*)() const) &ShapeAnalysis_TransferParametersProj::IsSameRange, "Returns False;");
cls_ShapeAnalysis_TransferParametersProj.def_static("CopyNMVertex_", (TopoDS_Vertex (*)(const TopoDS_Vertex &, const TopoDS_Edge &, const TopoDS_Edge &)) &ShapeAnalysis_TransferParametersProj::CopyNMVertex, "Make a copy of non-manifold vertex theVert (i.e. create new TVertex and replace PointRepresentations for this vertex from fromedge to toedge. Other representations were copied)", py::arg("theVert"), py::arg("toedge"), py::arg("fromedge"));
cls_ShapeAnalysis_TransferParametersProj.def_static("CopyNMVertex_", (TopoDS_Vertex (*)(const TopoDS_Vertex &, const TopoDS_Face &, const TopoDS_Face &)) &ShapeAnalysis_TransferParametersProj::CopyNMVertex, "Make a copy of non-manifold vertex theVert (i.e. create new TVertex and replace PointRepresentations for this vertex from fromFace to toFace. Other representations were copied)", py::arg("theVert"), py::arg("toFace"), py::arg("fromFace"));
cls_ShapeAnalysis_TransferParametersProj.def_static("get_type_name_", (const char * (*)()) &ShapeAnalysis_TransferParametersProj::get_type_name, "None");
cls_ShapeAnalysis_TransferParametersProj.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &ShapeAnalysis_TransferParametersProj::get_type_descriptor, "None");
cls_ShapeAnalysis_TransferParametersProj.def("DynamicType", (const opencascade::handle<Standard_Type> & (ShapeAnalysis_TransferParametersProj::*)() const) &ShapeAnalysis_TransferParametersProj::DynamicType, "None");

// CLASS: SHAPEANALYSIS_WIRE
py::class_<ShapeAnalysis_Wire, opencascade::handle<ShapeAnalysis_Wire>, Standard_Transient> cls_ShapeAnalysis_Wire(mod, "ShapeAnalysis_Wire", "This class provides analysis of a wire to be compliant to CAS.CADE requirements.");

// Constructors
cls_ShapeAnalysis_Wire.def(py::init<>());
cls_ShapeAnalysis_Wire.def(py::init<const TopoDS_Wire &, const TopoDS_Face &, const Standard_Real>(), py::arg("wire"), py::arg("face"), py::arg("precision"));
cls_ShapeAnalysis_Wire.def(py::init<const opencascade::handle<ShapeExtend_WireData> &, const TopoDS_Face &, const Standard_Real>(), py::arg("sbwd"), py::arg("face"), py::arg("precision"));

// Methods
cls_ShapeAnalysis_Wire.def("Init", (void (ShapeAnalysis_Wire::*)(const TopoDS_Wire &, const TopoDS_Face &, const Standard_Real)) &ShapeAnalysis_Wire::Init, "Initializes the object with standard TopoDS_Wire, face and precision", py::arg("wire"), py::arg("face"), py::arg("precision"));
cls_ShapeAnalysis_Wire.def("Init", (void (ShapeAnalysis_Wire::*)(const opencascade::handle<ShapeExtend_WireData> &, const TopoDS_Face &, const Standard_Real)) &ShapeAnalysis_Wire::Init, "Initializes the object with WireData object, face and precision", py::arg("sbwd"), py::arg("face"), py::arg("precision"));
cls_ShapeAnalysis_Wire.def("Load", (void (ShapeAnalysis_Wire::*)(const TopoDS_Wire &)) &ShapeAnalysis_Wire::Load, "Loads the object with standard TopoDS_Wire", py::arg("wire"));
cls_ShapeAnalysis_Wire.def("Load", (void (ShapeAnalysis_Wire::*)(const opencascade::handle<ShapeExtend_WireData> &)) &ShapeAnalysis_Wire::Load, "Loads the object with WireData object", py::arg("sbwd"));
cls_ShapeAnalysis_Wire.def("SetFace", (void (ShapeAnalysis_Wire::*)(const TopoDS_Face &)) &ShapeAnalysis_Wire::SetFace, "Loads the face the wire lies on", py::arg("face"));
cls_ShapeAnalysis_Wire.def("SetSurface", (void (ShapeAnalysis_Wire::*)(const opencascade::handle<Geom_Surface> &)) &ShapeAnalysis_Wire::SetSurface, "Loads the surface the wire lies on", py::arg("surface"));
cls_ShapeAnalysis_Wire.def("SetSurface", (void (ShapeAnalysis_Wire::*)(const opencascade::handle<Geom_Surface> &, const TopLoc_Location &)) &ShapeAnalysis_Wire::SetSurface, "Loads the surface the wire lies on", py::arg("surface"), py::arg("location"));
cls_ShapeAnalysis_Wire.def("SetPrecision", (void (ShapeAnalysis_Wire::*)(const Standard_Real)) &ShapeAnalysis_Wire::SetPrecision, "None", py::arg("precision"));
cls_ShapeAnalysis_Wire.def("ClearStatuses", (void (ShapeAnalysis_Wire::*)()) &ShapeAnalysis_Wire::ClearStatuses, "Unsets all the status and distance fields wire, face and precision are not cleared");
cls_ShapeAnalysis_Wire.def("IsLoaded", (Standard_Boolean (ShapeAnalysis_Wire::*)() const) &ShapeAnalysis_Wire::IsLoaded, "Returns True if wire is loaded and has number of edges >0");
cls_ShapeAnalysis_Wire.def("IsReady", (Standard_Boolean (ShapeAnalysis_Wire::*)() const) &ShapeAnalysis_Wire::IsReady, "Returns True if IsLoaded and underlying face is not null");
cls_ShapeAnalysis_Wire.def("Precision", (Standard_Real (ShapeAnalysis_Wire::*)() const) &ShapeAnalysis_Wire::Precision, "Returns the value of precision");
cls_ShapeAnalysis_Wire.def("WireData", (const opencascade::handle<ShapeExtend_WireData> & (ShapeAnalysis_Wire::*)() const) &ShapeAnalysis_Wire::WireData, "Returns wire object being analyzed");
cls_ShapeAnalysis_Wire.def("NbEdges", (Standard_Integer (ShapeAnalysis_Wire::*)() const) &ShapeAnalysis_Wire::NbEdges, "Returns the number of edges in the wire, or 0 if it is not loaded");
cls_ShapeAnalysis_Wire.def("Face", (const TopoDS_Face & (ShapeAnalysis_Wire::*)() const) &ShapeAnalysis_Wire::Face, "Returns the working face");
cls_ShapeAnalysis_Wire.def("Surface", (const opencascade::handle<ShapeAnalysis_Surface> & (ShapeAnalysis_Wire::*)() const) &ShapeAnalysis_Wire::Surface, "Returns the working surface");
cls_ShapeAnalysis_Wire.def("Perform", (Standard_Boolean (ShapeAnalysis_Wire::*)()) &ShapeAnalysis_Wire::Perform, "Performs all the checks in the following order : CheckOrder, CheckSmall, CheckConected, CheckEdgeCurves, CheckDegenerated, CheckSelfIntersection, CheckLacking, CheckClosed Returns: True if at least one method returned True; For deeper analysis use Status...(status) methods");
cls_ShapeAnalysis_Wire.def("CheckOrder", [](ShapeAnalysis_Wire &self) -> Standard_Boolean { return self.CheckOrder(); });
cls_ShapeAnalysis_Wire.def("CheckOrder", [](ShapeAnalysis_Wire &self, const Standard_Boolean a0) -> Standard_Boolean { return self.CheckOrder(a0); });
cls_ShapeAnalysis_Wire.def("CheckOrder", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Boolean, const Standard_Boolean)) &ShapeAnalysis_Wire::CheckOrder, "Calls CheckOrder and returns False if wire is already ordered (tail-to-head), True otherwise Flag <isClosed> defines if the wire is closed or not Flag <mode3d> defines which mode is used (3d or 2d)", py::arg("isClosed"), py::arg("mode3d"));
cls_ShapeAnalysis_Wire.def("CheckConnected", [](ShapeAnalysis_Wire &self) -> Standard_Boolean { return self.CheckConnected(); });
cls_ShapeAnalysis_Wire.def("CheckConnected", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Real)) &ShapeAnalysis_Wire::CheckConnected, "Calls to CheckConnected for each edge Returns: True if at least one pair of disconnected edges (not sharing the same vertex) was detected", py::arg("prec"));
cls_ShapeAnalysis_Wire.def("CheckSmall", [](ShapeAnalysis_Wire &self) -> Standard_Boolean { return self.CheckSmall(); });
cls_ShapeAnalysis_Wire.def("CheckSmall", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Real)) &ShapeAnalysis_Wire::CheckSmall, "Calls to CheckSmall for each edge Returns: True if at least one small edge was detected", py::arg("precsmall"));
cls_ShapeAnalysis_Wire.def("CheckEdgeCurves", (Standard_Boolean (ShapeAnalysis_Wire::*)()) &ShapeAnalysis_Wire::CheckEdgeCurves, "Checks edges geometry (consitency of 2d and 3d senses, adjasment of curves to the vertices, etc.). The order of the checks : Call ShapeAnalysis_Wire to check: ShapeAnalysis_Edge::CheckCurve3dWithPCurve (1), ShapeAnalysis_Edge::CheckVertcesWithPCurve (2), ShapeAnalysis_Edge::CheckVertcesWithCurve3d (3), CheckSeam (4) Additional: CheckGap3d (5), CheckGap2d (6), ShapeAnalysis_Edge::CheckSameParameter (7) Returns: True if at least one check returned True Remark: The numbers in brackets show with what DONEi or FAILi the status can be queried");
cls_ShapeAnalysis_Wire.def("CheckDegenerated", (Standard_Boolean (ShapeAnalysis_Wire::*)()) &ShapeAnalysis_Wire::CheckDegenerated, "Calls to CheckDegenerated for each edge Returns: True if at least one incorrect degenerated edge was detected");
cls_ShapeAnalysis_Wire.def("CheckClosed", [](ShapeAnalysis_Wire &self) -> Standard_Boolean { return self.CheckClosed(); });
cls_ShapeAnalysis_Wire.def("CheckClosed", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Real)) &ShapeAnalysis_Wire::CheckClosed, "Checks if wire is closed, performs CheckConnected, CheckDegenerated and CheckLacking for the first and the last edges Returns: True if at least one check returned True Status: FAIL1 or DONE1: see CheckConnected FAIL2 or DONE2: see CheckDegenerated", py::arg("prec"));
cls_ShapeAnalysis_Wire.def("CheckSelfIntersection", (Standard_Boolean (ShapeAnalysis_Wire::*)()) &ShapeAnalysis_Wire::CheckSelfIntersection, "Checks self-intersection of the wire (considering pcurves) Looks for self-intersecting edges and each pair of intersecting edges. Warning: It does not check each edge with any other one (only each two adjacent edges) The order of the checks : CheckSelfIntersectingEdge, CheckIntersectingEdges Returns: True if at least one check returned True Status: FAIL1 or DONE1 - see CheckSelfIntersectingEdge FAIL2 or DONE2 - see CheckIntersectingEdges");
cls_ShapeAnalysis_Wire.def("CheckLacking", (Standard_Boolean (ShapeAnalysis_Wire::*)()) &ShapeAnalysis_Wire::CheckLacking, "Calls to CheckLacking for each edge Returns: True if at least one lacking edge was detected");
cls_ShapeAnalysis_Wire.def("CheckGaps3d", (Standard_Boolean (ShapeAnalysis_Wire::*)()) &ShapeAnalysis_Wire::CheckGaps3d, "None");
cls_ShapeAnalysis_Wire.def("CheckGaps2d", (Standard_Boolean (ShapeAnalysis_Wire::*)()) &ShapeAnalysis_Wire::CheckGaps2d, "None");
cls_ShapeAnalysis_Wire.def("CheckCurveGaps", (Standard_Boolean (ShapeAnalysis_Wire::*)()) &ShapeAnalysis_Wire::CheckCurveGaps, "None");
cls_ShapeAnalysis_Wire.def("CheckOrder", [](ShapeAnalysis_Wire &self, ShapeAnalysis_WireOrder & a0) -> Standard_Boolean { return self.CheckOrder(a0); });
cls_ShapeAnalysis_Wire.def("CheckOrder", [](ShapeAnalysis_Wire &self, ShapeAnalysis_WireOrder & a0, const Standard_Boolean a1) -> Standard_Boolean { return self.CheckOrder(a0, a1); });
cls_ShapeAnalysis_Wire.def("CheckOrder", (Standard_Boolean (ShapeAnalysis_Wire::*)(ShapeAnalysis_WireOrder &, const Standard_Boolean, const Standard_Boolean)) &ShapeAnalysis_Wire::CheckOrder, "Analyzes the order of the edges in the wire, uses class WireOrder for that purpose. Flag <isClosed> defines if the wire is closed or not Flag <mode3d> defines which mode is used (3d or 2d) Returns False if wire is already ordered (tail-to-head), True otherwise. Use returned WireOrder object for deeper analysis. Status: OK : the same edges orientation, the same edges sequence DONE1: the same edges orientation, not the same edges sequence DONE2: as DONE1 and gaps more than myPrecision DONE3: not the same edges orientation (some need to be reversed) DONE4: as DONE3 and gaps more than myPrecision FAIL : algorithm failed (could not detect order)", py::arg("sawo"), py::arg("isClosed"), py::arg("mode3d"));
cls_ShapeAnalysis_Wire.def("CheckConnected", [](ShapeAnalysis_Wire &self, const Standard_Integer a0) -> Standard_Boolean { return self.CheckConnected(a0); });
cls_ShapeAnalysis_Wire.def("CheckConnected", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer, const Standard_Real)) &ShapeAnalysis_Wire::CheckConnected, "Checks connected edges (num-th and preceeding). Tests with starting preci from <SBWD> or with <prec> if it is greater. Considers Vertices. Returns: False if edges are connected by the common vertex, else True Status : OK : Vertices (end of num-1 th edge and start on num-th one) are already the same DONE1 : Absolutely confused (gp::Resolution) DONE2 : Confused at starting <preci> from <SBWD> DONE3 : Confused at <prec> but not <preci> FAIL1 : Not confused FAIL2 : Not confused but confused with <preci> if reverse num-th edge", py::arg("num"), py::arg("prec"));
cls_ShapeAnalysis_Wire.def("CheckSmall", [](ShapeAnalysis_Wire &self, const Standard_Integer a0) -> Standard_Boolean { return self.CheckSmall(a0); });
cls_ShapeAnalysis_Wire.def("CheckSmall", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer, const Standard_Real)) &ShapeAnalysis_Wire::CheckSmall, "Checks if an edge has a length not greater than myPreci or precsmall (if it is smaller) Returns: False if its length is greater than precision Status: OK : edge is not small or degenerated DONE1: edge is small, vertices are the same DONE2: edge is small, vertices are not the same FAIL : no 3d curve and pcurve", py::arg("num"), py::arg("precsmall"));
cls_ShapeAnalysis_Wire.def("CheckSeam", [](ShapeAnalysis_Wire &self, const Standard_Integer num, opencascade::handle<Geom2d_Curve> & C1, opencascade::handle<Geom2d_Curve> & C2, Standard_Real & cf, Standard_Real & cl){ Standard_Boolean rv = self.CheckSeam(num, C1, C2, cf, cl); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &>(rv, cf, cl); }, "Checks if a seam pcurves are correct oriented Returns: False (status OK) if given edge is not a seam or if it is OK C1 - current pcurve for FORWARD edge, C2 - current pcurve for REVERSED edge (if returns True they should be swapped for the seam), cf, cl - first and last parameters on curves Status: OK : Pcurves are correct or edge is not seam DONE : Seam pcurves should be swapped", py::arg("num"), py::arg("C1"), py::arg("C2"), py::arg("cf"), py::arg("cl"));
cls_ShapeAnalysis_Wire.def("CheckSeam", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer)) &ShapeAnalysis_Wire::CheckSeam, "Checks if a seam pcurves are correct oriented See previous functions for details", py::arg("num"));
cls_ShapeAnalysis_Wire.def("CheckDegenerated", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer, gp_Pnt2d &, gp_Pnt2d &)) &ShapeAnalysis_Wire::CheckDegenerated, "Checks for degenerated edge between two adjacent ones. Fills parameters dgnr1 and dgnr2 with points in paramterical space that correspond to the singularity (either gap that needs to be filled by degenerated edge or that already filled) Returns: False if no singularity or edge is already degenerated, otherwise True Status: OK : No surface singularity, or edge is already degenerated DONE1: Degenerated edge should be inserted (gap in 2D) DONE2: Edge <num> should be made degenerated (recompute pcurve and set the flag) FAIL1: One of edges neighbouring to degenerated one has no pcurve FAIL2: Edge marked as degenerated and has no pcurve but singularity is not detected", py::arg("num"), py::arg("dgnr1"), py::arg("dgnr2"));
cls_ShapeAnalysis_Wire.def("CheckDegenerated", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer)) &ShapeAnalysis_Wire::CheckDegenerated, "Checks for degenerated edge between two adjacent ones. Remark : Calls previous function Status : See the function above for details", py::arg("num"));
cls_ShapeAnalysis_Wire.def("CheckGap3d", [](ShapeAnalysis_Wire &self) -> Standard_Boolean { return self.CheckGap3d(); });
cls_ShapeAnalysis_Wire.def("CheckGap3d", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer)) &ShapeAnalysis_Wire::CheckGap3d, "Checks gap between edges in 3D (3d curves). Checks the distance between ends of 3d curves of the num-th and preceeding edge. The distance can be queried by MinDistance3d.", py::arg("num"));
cls_ShapeAnalysis_Wire.def("CheckGap2d", [](ShapeAnalysis_Wire &self) -> Standard_Boolean { return self.CheckGap2d(); });
cls_ShapeAnalysis_Wire.def("CheckGap2d", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer)) &ShapeAnalysis_Wire::CheckGap2d, "Checks gap between edges in 2D (pcurves). Checks the distance between ends of pcurves of the num-th and preceeding edge. The distance can be queried by MinDistance2d.", py::arg("num"));
cls_ShapeAnalysis_Wire.def("CheckCurveGap", [](ShapeAnalysis_Wire &self) -> Standard_Boolean { return self.CheckCurveGap(); });
cls_ShapeAnalysis_Wire.def("CheckCurveGap", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer)) &ShapeAnalysis_Wire::CheckCurveGap, "Checks gap between points on 3D curve and points on surface generated by pcurve of the num-th edge. The distance can be queried by MinDistance3d.", py::arg("num"));
cls_ShapeAnalysis_Wire.def("CheckSelfIntersectingEdge", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer, IntRes2d_SequenceOfIntersectionPoint &, TColgp_SequenceOfPnt &)) &ShapeAnalysis_Wire::CheckSelfIntersectingEdge, "Checks if num-th edge is self-intersecting. Self-intersection is reported only if intersection point lies outside of both end vertices of the edge. Returns: True if edge is self-intersecting. If returns True it also fills the sequences of intersection points and corresponding 3d points (only that are not enclosed by a vertices) Status: FAIL1 : No pcurve FAIL2 : No vertices DONE1 : Self-intersection found", py::arg("num"), py::arg("points2d"), py::arg("points3d"));
cls_ShapeAnalysis_Wire.def("CheckSelfIntersectingEdge", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer)) &ShapeAnalysis_Wire::CheckSelfIntersectingEdge, "None", py::arg("num"));
cls_ShapeAnalysis_Wire.def("CheckIntersectingEdges", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer, IntRes2d_SequenceOfIntersectionPoint &, TColgp_SequenceOfPnt &, TColStd_SequenceOfReal &)) &ShapeAnalysis_Wire::CheckIntersectingEdges, "Checks two adjacent edges for intersecting. Intersection is reported only if intersection point is not enclosed by the common end vertex of the edges. Returns: True if intersection is found. If returns True it also fills the sequences of intersection points, corresponding 3d points, and errors for them (half-distances between intersection points in 3d calculated from one and from another edge) Status: FAIL1 : No pcurve FAIL2 : No vertices DONE1 : Self-intersection found", py::arg("num"), py::arg("points2d"), py::arg("points3d"), py::arg("errors"));
cls_ShapeAnalysis_Wire.def("CheckIntersectingEdges", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer)) &ShapeAnalysis_Wire::CheckIntersectingEdges, "Checks two adjacent edges for intersecting. Remark : Calls the previous method Status : See the function above for details", py::arg("num"));
cls_ShapeAnalysis_Wire.def("CheckIntersectingEdges", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer, const Standard_Integer, IntRes2d_SequenceOfIntersectionPoint &, TColgp_SequenceOfPnt &, TColStd_SequenceOfReal &)) &ShapeAnalysis_Wire::CheckIntersectingEdges, "Checks i-th and j-th edges for intersecting. Remark : See the previous method for details", py::arg("num1"), py::arg("num2"), py::arg("points2d"), py::arg("points3d"), py::arg("errors"));
cls_ShapeAnalysis_Wire.def("CheckIntersectingEdges", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer, const Standard_Integer)) &ShapeAnalysis_Wire::CheckIntersectingEdges, "Checks i-th and j-th edges for intersecting. Remark : Calls previous method. Status : See the function above for details", py::arg("num1"), py::arg("num2"));
cls_ShapeAnalysis_Wire.def("CheckLacking", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer, const Standard_Real, gp_Pnt2d &, gp_Pnt2d &)) &ShapeAnalysis_Wire::CheckLacking, "Checks if there is a gap in 2d between edges, not comprised by the tolerance of their common vertex. If <Tolerance> is greater than 0. and less than tolerance of the vertex, then this value is used for check. Returns: True if not closed gap was detected p2d1 and p2d2 are the endpoint of <num-1>th edge and start of the <num>th edge in 2d. Status: OK: No edge is lacking (3d and 2d connection) FAIL1: edges have no vertices (at least one of them) FAIL2: edges are neither connected by common vertex, nor have coincided vertices FAIL1: edges have no pcurves DONE1: the gap is detected which cannot be closed by the tolerance of the common vertex (or with value of <Tolerance>) DONE2: is set (together with DONE1) if gap is detected and the vector (p2d2 - p2d1) goes in direction opposite to the pcurves of the edges (if angle is more than 0.9*PI).", py::arg("num"), py::arg("Tolerance"), py::arg("p2d1"), py::arg("p2d2"));
cls_ShapeAnalysis_Wire.def("CheckLacking", [](ShapeAnalysis_Wire &self, const Standard_Integer a0) -> Standard_Boolean { return self.CheckLacking(a0); });
cls_ShapeAnalysis_Wire.def("CheckLacking", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Integer, const Standard_Real)) &ShapeAnalysis_Wire::CheckLacking, "Checks if there is a gap in 2D between edges and not comprised by vertex tolerance The value of SBWD.thepreci is used. Returns: False if no edge should be inserted Status: OK : No edge is lacking (3d and 2d connection) DONE1 : The vertex tolerance should be increased only (2d gap is small) DONE2 : Edge can be inserted (3d and 2d gaps are large enough)", py::arg("num"), py::arg("Tolerance"));
cls_ShapeAnalysis_Wire.def("CheckOuterBound", [](ShapeAnalysis_Wire &self) -> Standard_Boolean { return self.CheckOuterBound(); });
cls_ShapeAnalysis_Wire.def("CheckOuterBound", (Standard_Boolean (ShapeAnalysis_Wire::*)(const Standard_Boolean)) &ShapeAnalysis_Wire::CheckOuterBound, "Checks if wire defines an outer bound on the face Uses ShapeAnalysis::IsOuterBound for analysis If <APIMake> is True uses BRepAPI_MakeWire to build the wire, if False (to be used only when edges share common vertices) uses BRep_Builder to build the wire", py::arg("APIMake"));
cls_ShapeAnalysis_Wire.def("CheckNotchedEdges", [](ShapeAnalysis_Wire &self, const Standard_Integer num, Standard_Integer & shortNum, Standard_Real & param, const Standard_Real Tolerance){ Standard_Boolean rv = self.CheckNotchedEdges(num, shortNum, param, Tolerance); return std::tuple<Standard_Boolean, Standard_Integer &, Standard_Real &>(rv, shortNum, param); }, "Detects a notch", py::arg("num"), py::arg("shortNum"), py::arg("param"), py::arg("Tolerance"));
cls_ShapeAnalysis_Wire.def("CheckSmallArea", (Standard_Boolean (ShapeAnalysis_Wire::*)(const TopoDS_Wire &)) &ShapeAnalysis_Wire::CheckSmallArea, "Checks if wire has parametric area less than precision.", py::arg("theWire"));
cls_ShapeAnalysis_Wire.def("CheckShapeConnect", [](ShapeAnalysis_Wire &self, const TopoDS_Shape & a0) -> Standard_Boolean { return self.CheckShapeConnect(a0); });
cls_ShapeAnalysis_Wire.def("CheckShapeConnect", (Standard_Boolean (ShapeAnalysis_Wire::*)(const TopoDS_Shape &, const Standard_Real)) &ShapeAnalysis_Wire::CheckShapeConnect, "Checks with what orientation <shape> (wire or edge) can be connected to the wire. Tests distances with starting <preci> from <SBWD> (close confusion), but if given <prec> is greater, tests with <prec> (coarse confusion). The smallest found distance can be returned by MinDistance3d", py::arg("shape"), py::arg("prec"));
cls_ShapeAnalysis_Wire.def("CheckShapeConnect", [](ShapeAnalysis_Wire &self, Standard_Real & tailhead, Standard_Real & tailtail, Standard_Real & headtail, Standard_Real & headhead, const TopoDS_Shape & shape, const Standard_Real prec){ Standard_Boolean rv = self.CheckShapeConnect(tailhead, tailtail, headtail, headhead, shape, prec); return std::tuple<Standard_Boolean, Standard_Real &, Standard_Real &, Standard_Real &, Standard_Real &>(rv, tailhead, tailtail, headtail, headhead); }, "The same as previous CheckShapeConnect but is more advanced. It returns the distances between each end of <sbwd> and each end of <shape>. For example, <tailhead> stores distance between tail of <sbwd> and head of <shape> Remark: First method CheckShapeConnect calls this one", py::arg("tailhead"), py::arg("tailtail"), py::arg("headtail"), py::arg("headhead"), py::arg("shape"), py::arg("prec"));
cls_ShapeAnalysis_Wire.def("CheckLoop", (Standard_Boolean (ShapeAnalysis_Wire::*)(TopTools_IndexedMapOfShape &, TopTools_DataMapOfShapeListOfShape &, TopTools_MapOfShape &, TopTools_MapOfShape &)) &ShapeAnalysis_Wire::CheckLoop, "Checks existance of loop on wire and return vertices wich are loop vertices (vertices belonging to a few pairs of edges)", py::arg("aMapLoopVertices"), py::arg("aMapVertexEdges"), py::arg("aMapSmallEdges"), py::arg("aMapSeemEdges"));
cls_ShapeAnalysis_Wire.def("CheckTail", (Standard_Boolean (ShapeAnalysis_Wire::*)(const TopoDS_Edge &, const TopoDS_Edge &, const Standard_Real, const Standard_Real, const Standard_Real, TopoDS_Edge &, TopoDS_Edge &, TopoDS_Edge &, TopoDS_Edge &)) &ShapeAnalysis_Wire::CheckTail, "None", py::arg("theEdge1"), py::arg("theEdge2"), py::arg("theMaxSine"), py::arg("theMaxWidth"), py::arg("theMaxTolerance"), py::arg("theEdge11"), py::arg("theEdge12"), py::arg("theEdge21"), py::arg("theEdge22"));
cls_ShapeAnalysis_Wire.def("StatusOrder", (Standard_Boolean (ShapeAnalysis_Wire::*)(const ShapeExtend_Status) const) &ShapeAnalysis_Wire::StatusOrder, "None", py::arg("Status"));
cls_ShapeAnalysis_Wire.def("StatusConnected", (Standard_Boolean (ShapeAnalysis_Wire::*)(const ShapeExtend_Status) const) &ShapeAnalysis_Wire::StatusConnected, "None", py::arg("Status"));
cls_ShapeAnalysis_Wire.def("StatusEdgeCurves", (Standard_Boolean (ShapeAnalysis_Wire::*)(const ShapeExtend_Status) const) &ShapeAnalysis_Wire::StatusEdgeCurves, "None", py::arg("Status"));
cls_ShapeAnalysis_Wire.def("StatusDegenerated", (Standard_Boolean (ShapeAnalysis_Wire::*)(const ShapeExtend_Status) const) &ShapeAnalysis_Wire::StatusDegenerated, "None", py::arg("Status"));
cls_ShapeAnalysis_Wire.def("StatusClosed", (Standard_Boolean (ShapeAnalysis_Wire::*)(const ShapeExtend_Status) const) &ShapeAnalysis_Wire::StatusClosed, "None", py::arg("Status"));
cls_ShapeAnalysis_Wire.def("StatusSmall", (Standard_Boolean (ShapeAnalysis_Wire::*)(const ShapeExtend_Status) const) &ShapeAnalysis_Wire::StatusSmall, "None", py::arg("Status"));
cls_ShapeAnalysis_Wire.def("StatusSelfIntersection", (Standard_Boolean (ShapeAnalysis_Wire::*)(const ShapeExtend_Status) const) &ShapeAnalysis_Wire::StatusSelfIntersection, "None", py::arg("Status"));
cls_ShapeAnalysis_Wire.def("StatusLacking", (Standard_Boolean (ShapeAnalysis_Wire::*)(const ShapeExtend_Status) const) &ShapeAnalysis_Wire::StatusLacking, "None", py::arg("Status"));
cls_ShapeAnalysis_Wire.def("StatusGaps3d", (Standard_Boolean (ShapeAnalysis_Wire::*)(const ShapeExtend_Status) const) &ShapeAnalysis_Wire::StatusGaps3d, "None", py::arg("Status"));
cls_ShapeAnalysis_Wire.def("StatusGaps2d", (Standard_Boolean (ShapeAnalysis_Wire::*)(const ShapeExtend_Status) const) &ShapeAnalysis_Wire::StatusGaps2d, "None", py::arg("Status"));
cls_ShapeAnalysis_Wire.def("StatusCurveGaps", (Standard_Boolean (ShapeAnalysis_Wire::*)(const ShapeExtend_Status) const) &ShapeAnalysis_Wire::StatusCurveGaps, "None", py::arg("Status"));
cls_ShapeAnalysis_Wire.def("StatusLoop", (Standard_Boolean (ShapeAnalysis_Wire::*)(const ShapeExtend_Status) const) &ShapeAnalysis_Wire::StatusLoop, "None", py::arg("Status"));
cls_ShapeAnalysis_Wire.def("LastCheckStatus", (Standard_Boolean (ShapeAnalysis_Wire::*)(const ShapeExtend_Status) const) &ShapeAnalysis_Wire::LastCheckStatus, "Querying the status of the LAST perfomed 'Advanced' checking procedure", py::arg("Status"));
cls_ShapeAnalysis_Wire.def("MinDistance3d", (Standard_Real (ShapeAnalysis_Wire::*)() const) &ShapeAnalysis_Wire::MinDistance3d, "Returns the last lowest distance in 3D computed by CheckOrientation, CheckConnected, CheckContinuity3d, CheckVertex, CheckNewVertex");
cls_ShapeAnalysis_Wire.def("MinDistance2d", (Standard_Real (ShapeAnalysis_Wire::*)() const) &ShapeAnalysis_Wire::MinDistance2d, "Returns the last lowest distance in 2D-UV computed by CheckContinuity2d");
cls_ShapeAnalysis_Wire.def("MaxDistance3d", (Standard_Real (ShapeAnalysis_Wire::*)() const) &ShapeAnalysis_Wire::MaxDistance3d, "Returns the last maximal distance in 3D computed by CheckOrientation, CheckConnected, CheckContinuity3d, CheckVertex, CheckNewVertex, CheckSameParameter");
cls_ShapeAnalysis_Wire.def("MaxDistance2d", (Standard_Real (ShapeAnalysis_Wire::*)() const) &ShapeAnalysis_Wire::MaxDistance2d, "Returns the last maximal distance in 2D-UV computed by CheckContinuity2d");
cls_ShapeAnalysis_Wire.def_static("get_type_name_", (const char * (*)()) &ShapeAnalysis_Wire::get_type_name, "None");
cls_ShapeAnalysis_Wire.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &ShapeAnalysis_Wire::get_type_descriptor, "None");
cls_ShapeAnalysis_Wire.def("DynamicType", (const opencascade::handle<Standard_Type> & (ShapeAnalysis_Wire::*)() const) &ShapeAnalysis_Wire::DynamicType, "None");

// CLASS: SHAPEANALYSIS_WIREORDER
py::class_<ShapeAnalysis_WireOrder> cls_ShapeAnalysis_WireOrder(mod, "ShapeAnalysis_WireOrder", "This class is intended to control and, if possible, redefine the order of a list of edges which define a wire Edges are not given directly, but as their bounds (start,end)");

// Constructors
cls_ShapeAnalysis_WireOrder.def(py::init<>());
cls_ShapeAnalysis_WireOrder.def(py::init<const Standard_Boolean, const Standard_Real>(), py::arg("mode3d"), py::arg("tol"));

// Methods
// cls_ShapeAnalysis_WireOrder.def_static("operator new_", (void * (*)(size_t)) &ShapeAnalysis_WireOrder::operator new, "None", py::arg("theSize"));
// cls_ShapeAnalysis_WireOrder.def_static("operator delete_", (void (*)(void *)) &ShapeAnalysis_WireOrder::operator delete, "None", py::arg("theAddress"));
// cls_ShapeAnalysis_WireOrder.def_static("operator new[]_", (void * (*)(size_t)) &ShapeAnalysis_WireOrder::operator new[], "None", py::arg("theSize"));
// cls_ShapeAnalysis_WireOrder.def_static("operator delete[]_", (void (*)(void *)) &ShapeAnalysis_WireOrder::operator delete[], "None", py::arg("theAddress"));
// cls_ShapeAnalysis_WireOrder.def_static("operator new_", (void * (*)(size_t, void *)) &ShapeAnalysis_WireOrder::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ShapeAnalysis_WireOrder.def_static("operator delete_", (void (*)(void *, void *)) &ShapeAnalysis_WireOrder::operator delete, "None", py::arg(""), py::arg(""));
cls_ShapeAnalysis_WireOrder.def("SetMode", (void (ShapeAnalysis_WireOrder::*)(const Standard_Boolean, const Standard_Real)) &ShapeAnalysis_WireOrder::SetMode, "Sets new values. Clears the connexion list If <mode3d> changes, also clears the edge list (else, doesnt)", py::arg("mode3d"), py::arg("tol"));
cls_ShapeAnalysis_WireOrder.def("Tolerance", (Standard_Real (ShapeAnalysis_WireOrder::*)() const) &ShapeAnalysis_WireOrder::Tolerance, "Returns the working tolerance");
cls_ShapeAnalysis_WireOrder.def("Clear", (void (ShapeAnalysis_WireOrder::*)()) &ShapeAnalysis_WireOrder::Clear, "Clears the list of edges, but not mode and tol");
cls_ShapeAnalysis_WireOrder.def("Add", (void (ShapeAnalysis_WireOrder::*)(const gp_XYZ &, const gp_XYZ &)) &ShapeAnalysis_WireOrder::Add, "Adds a couple of points 3D (start,end)", py::arg("start3d"), py::arg("end3d"));
cls_ShapeAnalysis_WireOrder.def("Add", (void (ShapeAnalysis_WireOrder::*)(const gp_XY &, const gp_XY &)) &ShapeAnalysis_WireOrder::Add, "Adds a couple of points 2D (start,end)", py::arg("start2d"), py::arg("end2d"));
cls_ShapeAnalysis_WireOrder.def("NbEdges", (Standard_Integer (ShapeAnalysis_WireOrder::*)() const) &ShapeAnalysis_WireOrder::NbEdges, "Returns the count of added couples of points (one per edges)");
cls_ShapeAnalysis_WireOrder.def("KeepLoopsMode", (Standard_Boolean & (ShapeAnalysis_WireOrder::*)()) &ShapeAnalysis_WireOrder::KeepLoopsMode, "If this mode is True method perform does not sort edges of different loops. The resulting order is first loop, second one etc...");
cls_ShapeAnalysis_WireOrder.def("Perform", [](ShapeAnalysis_WireOrder &self) -> void { return self.Perform(); });
cls_ShapeAnalysis_WireOrder.def("Perform", (void (ShapeAnalysis_WireOrder::*)(const Standard_Boolean)) &ShapeAnalysis_WireOrder::Perform, "Computes the better order If <closed> is True (D) considers also closure Optimised if the couples were already in order The criterium is : two couples in order if distance between end-prec and start-cur is less then starting tolerance <tol> Else, the smallest distance is reached Gap corresponds to a smallest distance greater than <tol>", py::arg("closed"));
cls_ShapeAnalysis_WireOrder.def("IsDone", (Standard_Boolean (ShapeAnalysis_WireOrder::*)() const) &ShapeAnalysis_WireOrder::IsDone, "Tells if Perform has been done Else, the following methods returns original values");
cls_ShapeAnalysis_WireOrder.def("Status", (Standard_Integer (ShapeAnalysis_WireOrder::*)() const) &ShapeAnalysis_WireOrder::Status, "Returns the status of the order (0 if not done) : 0 : all edges are direct and in sequence 1 : all edges are direct but some are not in sequence 2 : in addition, unresolved gaps remain -1 : some edges are reversed, but no gap remain -2 : some edges are reversed and some gaps remain -10 : COULD NOT BE RESOLVED, Failure on Reorder gap : regarding starting <tol>");
cls_ShapeAnalysis_WireOrder.def("Ordered", (Standard_Integer (ShapeAnalysis_WireOrder::*)(const Standard_Integer) const) &ShapeAnalysis_WireOrder::Ordered, "Returns the number of original edge which correspond to the newly ordered number <n> Warning : the returned value is NEGATIVE if edge should be reversed", py::arg("n"));
cls_ShapeAnalysis_WireOrder.def("XYZ", (void (ShapeAnalysis_WireOrder::*)(const Standard_Integer, gp_XYZ &, gp_XYZ &) const) &ShapeAnalysis_WireOrder::XYZ, "Returns the values of the couple <num>, as 3D values", py::arg("num"), py::arg("start3d"), py::arg("end3d"));
cls_ShapeAnalysis_WireOrder.def("XY", (void (ShapeAnalysis_WireOrder::*)(const Standard_Integer, gp_XY &, gp_XY &) const) &ShapeAnalysis_WireOrder::XY, "Returns the values of the couple <num>, as 2D values", py::arg("num"), py::arg("start2d"), py::arg("end2d"));
cls_ShapeAnalysis_WireOrder.def("Gap", [](ShapeAnalysis_WireOrder &self) -> Standard_Real { return self.Gap(); });
cls_ShapeAnalysis_WireOrder.def("Gap", (Standard_Real (ShapeAnalysis_WireOrder::*)(const Standard_Integer) const) &ShapeAnalysis_WireOrder::Gap, "Returns the gap between a couple and its preceeding <num> is considered ordered If <num> = 0 (D), returns the greatest gap found", py::arg("num"));
cls_ShapeAnalysis_WireOrder.def("SetChains", (void (ShapeAnalysis_WireOrder::*)(const Standard_Real)) &ShapeAnalysis_WireOrder::SetChains, "Determines the chains inside which successive edges have a gap less than a given value. Queried by NbChains and Chain", py::arg("gap"));
cls_ShapeAnalysis_WireOrder.def("NbChains", (Standard_Integer (ShapeAnalysis_WireOrder::*)() const) &ShapeAnalysis_WireOrder::NbChains, "Returns the count of computed chains");
cls_ShapeAnalysis_WireOrder.def("Chain", [](ShapeAnalysis_WireOrder &self, const Standard_Integer num, Standard_Integer & n1, Standard_Integer & n2){ self.Chain(num, n1, n2); return std::tuple<Standard_Integer &, Standard_Integer &>(n1, n2); }, "Returns, for the chain n0 num, starting and ending numbers of edges. In the list of ordered edges (see Ordered for originals)", py::arg("num"), py::arg("n1"), py::arg("n2"));
cls_ShapeAnalysis_WireOrder.def("SetCouples", (void (ShapeAnalysis_WireOrder::*)(const Standard_Real)) &ShapeAnalysis_WireOrder::SetCouples, "Determines the couples of edges for which end and start fit inside a given gap. Queried by NbCouples and Couple", py::arg("gap"));
cls_ShapeAnalysis_WireOrder.def("NbCouples", (Standard_Integer (ShapeAnalysis_WireOrder::*)() const) &ShapeAnalysis_WireOrder::NbCouples, "Returns the count of computed couples");
cls_ShapeAnalysis_WireOrder.def("Couple", [](ShapeAnalysis_WireOrder &self, const Standard_Integer num, Standard_Integer & n1, Standard_Integer & n2){ self.Couple(num, n1, n2); return std::tuple<Standard_Integer &, Standard_Integer &>(n1, n2); }, "Returns, for the couple n0 num, the two implied edges In the list of ordered edges", py::arg("num"), py::arg("n1"), py::arg("n2"));

// CLASS: SHAPEANALYSIS_WIREVERTEX
py::class_<ShapeAnalysis_WireVertex> cls_ShapeAnalysis_WireVertex(mod, "ShapeAnalysis_WireVertex", "Analyzes and records status of vertices in a Wire");

// Constructors
cls_ShapeAnalysis_WireVertex.def(py::init<>());

// Methods
// cls_ShapeAnalysis_WireVertex.def_static("operator new_", (void * (*)(size_t)) &ShapeAnalysis_WireVertex::operator new, "None", py::arg("theSize"));
// cls_ShapeAnalysis_WireVertex.def_static("operator delete_", (void (*)(void *)) &ShapeAnalysis_WireVertex::operator delete, "None", py::arg("theAddress"));
// cls_ShapeAnalysis_WireVertex.def_static("operator new[]_", (void * (*)(size_t)) &ShapeAnalysis_WireVertex::operator new[], "None", py::arg("theSize"));
// cls_ShapeAnalysis_WireVertex.def_static("operator delete[]_", (void (*)(void *)) &ShapeAnalysis_WireVertex::operator delete[], "None", py::arg("theAddress"));
// cls_ShapeAnalysis_WireVertex.def_static("operator new_", (void * (*)(size_t, void *)) &ShapeAnalysis_WireVertex::operator new, "None", py::arg(""), py::arg("theAddress"));
// cls_ShapeAnalysis_WireVertex.def_static("operator delete_", (void (*)(void *, void *)) &ShapeAnalysis_WireVertex::operator delete, "None", py::arg(""), py::arg(""));
cls_ShapeAnalysis_WireVertex.def("Init", (void (ShapeAnalysis_WireVertex::*)(const TopoDS_Wire &, const Standard_Real)) &ShapeAnalysis_WireVertex::Init, "None", py::arg("wire"), py::arg("preci"));
cls_ShapeAnalysis_WireVertex.def("Init", (void (ShapeAnalysis_WireVertex::*)(const opencascade::handle<ShapeExtend_WireData> &, const Standard_Real)) &ShapeAnalysis_WireVertex::Init, "None", py::arg("swbd"), py::arg("preci"));
cls_ShapeAnalysis_WireVertex.def("Load", (void (ShapeAnalysis_WireVertex::*)(const TopoDS_Wire &)) &ShapeAnalysis_WireVertex::Load, "None", py::arg("wire"));
cls_ShapeAnalysis_WireVertex.def("Load", (void (ShapeAnalysis_WireVertex::*)(const opencascade::handle<ShapeExtend_WireData> &)) &ShapeAnalysis_WireVertex::Load, "None", py::arg("sbwd"));
cls_ShapeAnalysis_WireVertex.def("SetPrecision", (void (ShapeAnalysis_WireVertex::*)(const Standard_Real)) &ShapeAnalysis_WireVertex::SetPrecision, "Sets the precision for work Analysing: for each Vertex, comparison between the end of the preceeding edge and the start of the following edge Each Vertex rank corresponds to the End Vertex of the Edge of same rank, in the ShapeExtend_WireData. I.E. for Vertex <num>, Edge <num> is the preceeding one, <num+1> is the following one", py::arg("preci"));
cls_ShapeAnalysis_WireVertex.def("Analyze", (void (ShapeAnalysis_WireVertex::*)()) &ShapeAnalysis_WireVertex::Analyze, "None");
cls_ShapeAnalysis_WireVertex.def("SetSameVertex", (void (ShapeAnalysis_WireVertex::*)(const Standard_Integer)) &ShapeAnalysis_WireVertex::SetSameVertex, "Records status 'Same Vertex' (logically) on Vertex <num>", py::arg("num"));
cls_ShapeAnalysis_WireVertex.def("SetSameCoords", (void (ShapeAnalysis_WireVertex::*)(const Standard_Integer)) &ShapeAnalysis_WireVertex::SetSameCoords, "Records status 'Same Coords' (at the Vertices Tolerances)", py::arg("num"));
cls_ShapeAnalysis_WireVertex.def("SetClose", (void (ShapeAnalysis_WireVertex::*)(const Standard_Integer)) &ShapeAnalysis_WireVertex::SetClose, "Records status 'Close Coords' (at the Precision of <me>)", py::arg("num"));
cls_ShapeAnalysis_WireVertex.def("SetEnd", (void (ShapeAnalysis_WireVertex::*)(const Standard_Integer, const gp_XYZ &, const Standard_Real)) &ShapeAnalysis_WireVertex::SetEnd, "<num> is the End of preceeding Edge, and its projection on the following one lies on it at the Precision of <me> <ufol> gives the parameter on the following edge", py::arg("num"), py::arg("pos"), py::arg("ufol"));
cls_ShapeAnalysis_WireVertex.def("SetStart", (void (ShapeAnalysis_WireVertex::*)(const Standard_Integer, const gp_XYZ &, const Standard_Real)) &ShapeAnalysis_WireVertex::SetStart, "<num> is the Start of following Edge, its projection on the preceeding one lies on it at the Precision of <me> <upre> gives the parameter on the preceeding edge", py::arg("num"), py::arg("pos"), py::arg("upre"));
cls_ShapeAnalysis_WireVertex.def("SetInters", (void (ShapeAnalysis_WireVertex::*)(const Standard_Integer, const gp_XYZ &, const Standard_Real, const Standard_Real)) &ShapeAnalysis_WireVertex::SetInters, "<num> is the Intersection of both Edges <upre> is the parameter on preceeding edge, <ufol> on following edge", py::arg("num"), py::arg("pos"), py::arg("upre"), py::arg("ufol"));
cls_ShapeAnalysis_WireVertex.def("SetDisjoined", (void (ShapeAnalysis_WireVertex::*)(const Standard_Integer)) &ShapeAnalysis_WireVertex::SetDisjoined, "<num> cannot be said as same vertex", py::arg("num"));
cls_ShapeAnalysis_WireVertex.def("IsDone", (Standard_Boolean (ShapeAnalysis_WireVertex::*)() const) &ShapeAnalysis_WireVertex::IsDone, "Returns True if analysis was performed, else returns False");
cls_ShapeAnalysis_WireVertex.def("Precision", (Standard_Real (ShapeAnalysis_WireVertex::*)() const) &ShapeAnalysis_WireVertex::Precision, "Returns precision value used in analysis");
cls_ShapeAnalysis_WireVertex.def("NbEdges", (Standard_Integer (ShapeAnalysis_WireVertex::*)() const) &ShapeAnalysis_WireVertex::NbEdges, "Returns the number of edges in analyzed wire (i.e. the length of all arrays)");
cls_ShapeAnalysis_WireVertex.def("WireData", (const opencascade::handle<ShapeExtend_WireData> & (ShapeAnalysis_WireVertex::*)() const) &ShapeAnalysis_WireVertex::WireData, "Returns analyzed wire");
cls_ShapeAnalysis_WireVertex.def("Status", (Standard_Integer (ShapeAnalysis_WireVertex::*)(const Standard_Integer) const) &ShapeAnalysis_WireVertex::Status, "Returns the recorded status for a vertex More detail by method Data", py::arg("num"));
cls_ShapeAnalysis_WireVertex.def("Position", (gp_XYZ (ShapeAnalysis_WireVertex::*)(const Standard_Integer) const) &ShapeAnalysis_WireVertex::Position, "None", py::arg("num"));
cls_ShapeAnalysis_WireVertex.def("UPrevious", (Standard_Real (ShapeAnalysis_WireVertex::*)(const Standard_Integer) const) &ShapeAnalysis_WireVertex::UPrevious, "None", py::arg("num"));
cls_ShapeAnalysis_WireVertex.def("UFollowing", (Standard_Real (ShapeAnalysis_WireVertex::*)(const Standard_Integer) const) &ShapeAnalysis_WireVertex::UFollowing, "None", py::arg("num"));
cls_ShapeAnalysis_WireVertex.def("Data", [](ShapeAnalysis_WireVertex &self, const Standard_Integer num, gp_XYZ & pos, Standard_Real & upre, Standard_Real & ufol){ Standard_Integer rv = self.Data(num, pos, upre, ufol); return std::tuple<Standard_Integer, Standard_Real &, Standard_Real &>(rv, upre, ufol); }, "Returns the recorded status for a vertex With its recorded position and parameters on both edges These values are relevant regarding the status: Status Meaning Position Preceeding Following 0 Same no no no 1 SameCoord no no no 2 Close no no no 3 End yes no yes 4 Start yes yes no 5 Inters yes yes yes -1 Disjoined no no no", py::arg("num"), py::arg("pos"), py::arg("upre"), py::arg("ufol"));
cls_ShapeAnalysis_WireVertex.def("NextStatus", [](ShapeAnalysis_WireVertex &self, const Standard_Integer a0) -> Standard_Integer { return self.NextStatus(a0); });
cls_ShapeAnalysis_WireVertex.def("NextStatus", (Standard_Integer (ShapeAnalysis_WireVertex::*)(const Standard_Integer, const Standard_Integer) const) &ShapeAnalysis_WireVertex::NextStatus, "For a given status, returns the rank of the vertex which follows <num> and has the same status. 0 if no more Acts as an iterator, starts on the first one", py::arg("stat"), py::arg("num"));
cls_ShapeAnalysis_WireVertex.def("NextCriter", [](ShapeAnalysis_WireVertex &self, const Standard_Integer a0) -> Standard_Integer { return self.NextCriter(a0); });
cls_ShapeAnalysis_WireVertex.def("NextCriter", (Standard_Integer (ShapeAnalysis_WireVertex::*)(const Standard_Integer, const Standard_Integer) const) &ShapeAnalysis_WireVertex::NextCriter, "For a given criter, returns the rank of the vertex which follows <num> and has the same status. 0 if no more Acts as an iterator, starts on the first one Criters are: 0: same vertex (status 0) 1: a solution exists (status >= 0) 2: same coords (i.e. same params) (status 0 1 2) 3: same coods but not same vertex (status 1 2) 4: redefined coords (status 3 4 5) -1: no solution (status -1)", py::arg("crit"), py::arg("num"));


}