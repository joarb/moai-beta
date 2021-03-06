// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moaicore/MOAIQuadBrush.h>
#include <moaicore/MOAIVertexFormatMgr.h>

//================================================================//
// MOAIQuadBrush
//================================================================//

//----------------------------------------------------------------//
void MOAIQuadBrush::BindVertexFormat ( MOAIGfxDevice& gfxDevice ) {
	
	gfxDevice.SetVertexPreset ( MOAIVertexFormatMgr::XYZWUVC );
	gfxDevice.SetPrimType ( GL_TRIANGLES );
}

//----------------------------------------------------------------//
void MOAIQuadBrush::Draw () {

	this->Draw ( this->mVtx, this->mUV );
}

//----------------------------------------------------------------//
void MOAIQuadBrush::Draw ( const USMatrix3x3& mtx ) {
	
	USVec2D vtx [ 4 ];
	
	vtx [ 0 ] = this->mVtx [ 0 ];
	vtx [ 1 ] = this->mVtx [ 1 ];
	vtx [ 2 ] = this->mVtx [ 2 ];
	vtx [ 3 ] = this->mVtx [ 3 ];
	
	mtx.Transform ( vtx [ 0 ]);
	mtx.Transform ( vtx [ 1 ]);
	mtx.Transform ( vtx [ 2 ]);
	mtx.Transform ( vtx [ 3 ]);
	
	this->Draw ( vtx, this->mUV );
}

//----------------------------------------------------------------//
void MOAIQuadBrush::Draw ( float xOff, float yOff ) {
	
	USVec2D vtx [ 4 ];
	
	vtx [ 0 ].mX = this->mVtx [ 0 ].mX + xOff;
	vtx [ 0 ].mY = this->mVtx [ 0 ].mY + yOff;
	
	vtx [ 1 ].mX = this->mVtx [ 1 ].mX + xOff;
	vtx [ 1 ].mY = this->mVtx [ 1 ].mY + yOff;
	
	vtx [ 2 ].mX = this->mVtx [ 2 ].mX + xOff;
	vtx [ 2 ].mY = this->mVtx [ 2 ].mY + yOff;
	
	vtx [ 3 ].mX = this->mVtx [ 3 ].mX + xOff;
	vtx [ 3 ].mY = this->mVtx [ 3 ].mY + yOff;
	
	this->Draw ( vtx, this->mUV );
}

//----------------------------------------------------------------//
void MOAIQuadBrush::Draw ( float xOff, float yOff, float xScale, float yScale ) {
	
	USVec2D vtx [ 4 ];
	
	vtx [ 0 ].mX = ( this->mVtx [ 0 ].mX * xScale ) + xOff;
	vtx [ 0 ].mY = ( this->mVtx [ 0 ].mY * yScale ) + yOff;
	
	vtx [ 1 ].mX = ( this->mVtx [ 1 ].mX * xScale ) + xOff;
	vtx [ 1 ].mY = ( this->mVtx [ 1 ].mY * yScale ) + yOff;

	vtx [ 2 ].mX = ( this->mVtx [ 2 ].mX * xScale ) + xOff;
	vtx [ 2 ].mY = ( this->mVtx [ 2 ].mY * yScale ) + yOff;
	
	vtx [ 3 ].mX = ( this->mVtx [ 3 ].mX * xScale ) + xOff;
	vtx [ 3 ].mY = ( this->mVtx [ 3 ].mY * yScale ) + yOff;
	
	this->Draw ( vtx, this->mUV );
}

//----------------------------------------------------------------//
void MOAIQuadBrush::Draw ( const USVec2D* vtx, const USVec2D* uv ) {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
		
	gfxDevice.WriteQuad (( USVec2D* )vtx, ( USVec2D* )uv ); 
}

//----------------------------------------------------------------//
USRect MOAIQuadBrush::GetUVBounds () {

	USRect rect;
	
	rect.Init ( this->mUV [ 0 ]);
	rect.Grow ( this->mUV [ 1 ]);
	rect.Grow ( this->mUV [ 2 ]);
	rect.Grow ( this->mUV [ 3 ]);
	
	return rect;
}

//----------------------------------------------------------------//
USRect MOAIQuadBrush::GetVtxBounds () {

	USRect rect;
	
	rect.Init ( this->mVtx [ 0 ]);
	rect.Grow ( this->mVtx [ 1 ]);
	rect.Grow ( this->mVtx [ 2 ]);
	rect.Grow ( this->mVtx [ 3 ]);
	
	return rect;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::ScaleUVs ( float xScale, float yScale ) {

	this->mUV [ 0 ].Scale ( xScale, yScale );
	this->mUV [ 1 ].Scale ( xScale, yScale );
	this->mUV [ 2 ].Scale ( xScale, yScale );
	this->mUV [ 3 ].Scale ( xScale, yScale );
}

//----------------------------------------------------------------//
void MOAIQuadBrush::ScaleVerts ( float xScale, float yScale ) {

	this->mVtx [ 0 ].Scale ( xScale, yScale );
	this->mVtx [ 1 ].Scale ( xScale, yScale );
	this->mVtx [ 2 ].Scale ( xScale, yScale );
	this->mVtx [ 3 ].Scale ( xScale, yScale );
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetUVs ( const USRect& rect ) {
	
	// left top
	this->mUV [ 0 ].mX = rect.mXMin;
	this->mUV [ 0 ].mY = rect.mYMax;
	
	// right top
	this->mUV [ 1 ].mX = rect.mXMax;
	this->mUV [ 1 ].mY = rect.mYMax;
	
	// right bottom
	this->mUV [ 2 ].mX = rect.mXMax;
	this->mUV [ 2 ].mY = rect.mYMin;
	
	// left bottom
	this->mUV [ 3 ].mX = rect.mXMin;
	this->mUV [ 3 ].mY = rect.mYMin;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetUVs ( float* buffer ) {

	// left top
	this->mUV [ 0 ].mX = buffer [ 0 ];
	this->mUV [ 0 ].mY = buffer [ 1 ];
	
	// right top
	this->mUV [ 1 ].mX = buffer [ 2 ];
	this->mUV [ 1 ].mY = buffer [ 3 ];
	
	// right bottom
	this->mUV [ 2 ].mX = buffer [ 4 ];
	this->mUV [ 2 ].mY = buffer [ 5 ];
	
	// left bottom
	this->mUV [ 3 ].mX = buffer [ 6 ];
	this->mUV [ 3 ].mY = buffer [ 7 ];
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetUVs ( float x0, float y0, float x1, float y1 ) {
	
	// left top
	this->mUV [ 0 ].mX = x0;
	this->mUV [ 0 ].mY = y1;
	
	// right top
	this->mUV [ 1 ].mX = x1;
	this->mUV [ 1 ].mY = y1;
	
	// right bottom
	this->mUV [ 2 ].mX = x1;
	this->mUV [ 2 ].mY = y0;
	
	// left bottom
	this->mUV [ 3 ].mX = x0;
	this->mUV [ 3 ].mY = y0;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetUVs ( const USVec2D& v0, const USVec2D& v1,const  USVec2D& v2, const USVec2D& v3 ) {

	// left top
	this->mUV [ 0 ] = v0;
	
	// right top
	this->mUV [ 1 ] = v1;
	
	// right bottom
	this->mUV [ 2 ] = v2;
	
	// left bottom
	this->mUV [ 3 ] = v3;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetUVs ( float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3 ) {

	// left top
	this->mUV [ 0 ].mX = x0;
	this->mUV [ 0 ].mY = y0;
	
	// right top
	this->mUV [ 1 ].mX = x1;
	this->mUV [ 1 ].mY = y1;
	
	// right bottom
	this->mUV [ 2 ].mX = x2;
	this->mUV [ 2 ].mY = y2;
	
	// left bottom
	this->mUV [ 3 ].mX = x3;
	this->mUV [ 3 ].mY = y3;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetVerts ( const USRect& rect ) {
	
	// left top
	this->mVtx [ 0 ].mX = rect.mXMin;
	this->mVtx [ 0 ].mY = rect.mYMax;
	
	// right top
	this->mVtx [ 1 ].mX = rect.mXMax;
	this->mVtx [ 1 ].mY = rect.mYMax;
	
	// right bottom
	this->mVtx [ 2 ].mX = rect.mXMax;
	this->mVtx [ 2 ].mY = rect.mYMin;
	
	// left bottom
	this->mVtx [ 3 ].mX = rect.mXMin;
	this->mVtx [ 3 ].mY = rect.mYMin;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetVerts ( float* buffer ) {

	// left top
	this->mVtx [ 0 ].mX = buffer [ 0 ];
	this->mVtx [ 0 ].mY = buffer [ 1 ];
	
	// right top
	this->mVtx [ 1 ].mX = buffer [ 2 ];
	this->mVtx [ 1 ].mY = buffer [ 3 ];
	
	// right bottom
	this->mVtx [ 2 ].mX = buffer [ 4 ];
	this->mVtx [ 2 ].mY = buffer [ 5 ];
	
	// left bottom
	this->mVtx [ 3 ].mX = buffer [ 6 ];
	this->mVtx [ 3 ].mY = buffer [ 7 ];
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetVerts ( float x0, float y0, float x1, float y1 ) {
	
	// left top
	this->mVtx [ 0 ].mX = x0;
	this->mVtx [ 0 ].mY = y1;
	
	// right top
	this->mVtx [ 1 ].mX = x1;
	this->mVtx [ 1 ].mY = y1;
	
	// right bottom
	this->mVtx [ 2 ].mX = x1;
	this->mVtx [ 2 ].mY = y0;
	
	// left bottom
	this->mVtx [ 3 ].mX = x0;
	this->mVtx [ 3 ].mY = y0;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetVerts ( const USVec2D& v0, const USVec2D& v1, const USVec2D& v2, const USVec2D& v3 ) {

	// left top
	this->mVtx [ 0 ] = v0;
	
	// right top
	this->mVtx [ 1 ] = v1;
	
	// right bottom
	this->mVtx [ 2 ] = v2;
	
	// left bottom
	this->mVtx [ 3 ] = v3;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetVerts ( float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3 ) {

	// left top
	this->mUV [ 0 ].mX = x0;
	this->mUV [ 0 ].mY = y0;
	
	// right top
	this->mUV [ 1 ].mX = x1;
	this->mUV [ 1 ].mY = y1;
	
	// right bottom
	this->mUV [ 2 ].mX = x2;
	this->mUV [ 2 ].mY = y2;
	
	// left bottom
	this->mUV [ 3 ].mX = x3;
	this->mUV [ 3 ].mY = y3;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetVerts ( const USVec2D& v0, float radius ) {

	this->SetVerts (
		v0.mX - radius,
		v0.mY - radius,
		v0.mX + radius,
		v0.mY + radius
	);
}

//----------------------------------------------------------------//
void MOAIQuadBrush::TransformVerts ( const USMatrix3x3& mtx ) {
	
	mtx.Transform ( this->mVtx [ 0 ]);
	mtx.Transform ( this->mVtx [ 1 ]);
	mtx.Transform ( this->mVtx [ 2 ]);
	mtx.Transform ( this->mVtx [ 3 ]);
}

//----------------------------------------------------------------//
void MOAIQuadBrush::TransformUVs ( const USMatrix3x3& mtx ) {

	mtx.Transform ( this->mUV [ 0 ]);
	mtx.Transform ( this->mUV [ 1 ]);
	mtx.Transform ( this->mUV [ 2 ]);
	mtx.Transform ( this->mUV [ 3 ]);
}
