//////////////////////////////////////////////////////////////////////
//
// 3D Studio Model Class
// by: Matthew Fairfax
//
// Model_3DS.h: interface for the Model_3DS class.
// This is a simple class for loading and viewing
// 3D Studio model files (.3ds). It supports models
// with multiple objects. It also supports multiple
// textures per object. It does not support the animation
// for 3D Studio models b/c there are simply too many
// ways for an artist to animate a 3D Studio model and
// I didn't want to impose huge limitations on the artists.
// However, I have imposed a limitation on how the models are
// textured:
// 1) Every faces must be assigned a material
// 2) If you want the face to be textured assign the
//    texture to the Diffuse Color map
// 3) The texture must be supported by the GLTexture class
//    which only supports bitmap and targa right now
// 4) The texture must be located in the same directory as
//    the model
//
// Support for non-textured faces is done by reading the color
// from the material's diffuse color.
//
// Some models have problems loading even if you follow all of
// the restrictions I have stated and I don't know why. If you
// can import the 3D Studio file into Milkshape 3D 
// (http://www.swissquake.ch/chumbalum-soft) and then export it
// to a new 3D Studio file. This seems to fix many of the problems
// but there is a limit on the number of faces and vertices Milkshape 3D
// can read.
//
// Usage:
// Model_3DS m;
//
// m.Load("model.3ds"); // Load the model
// m.Draw();			// Renders the model to the screen
//
// // If you want to show the model's normals
// m.shownormals = true;
//
// // If the model is not going to be lit then set the lit
// // variable to false. It defaults to true.
// m.lit = false;
//
// // You can disable the rendering of the model
// m.visible = false;
// 
// // You can move and rotate the model like this:
// m.rot.v[XDIM] = 90.0f;
// m.rot.v[YDIM] = 30.0f;
// m.rot.v[ZDIM] = 0.0f;
//
// m.pos.v[XDIM] = 10.0f;
// m.pos.v[YDIM] = 0.0f;
// m.pos.v[ZDIM] = 0.0f;
//
// // If you want to move or rotate individual objects
// m.Objects[0].rot.v[XDIM] = 90.0f;
// m.Objects[0].rot.v[YDIM] = 30.0f;
// m.Objects[0].rot.v[ZDIM] = 0.0f;
//
// m.Objects[0].pos.v[XDIM] = 10.0f;
// m.Objects[0].pos.v[YDIM] = 0.0f;
// m.Objects[0].pos.v[ZDIM] = 0.0f;
//
//////////////////////////////////////////////////////////////////////

// Modified by Santiago Piqueras, jan 2014

#ifndef MODEL_3DS_H
#define MODEL_3DS_H

#define MODEL_API_ASSIMP

// I decided to use my GLTexture class b/c adding all of its functions
// Would have greatly bloated the model class's code
// Just replace this with your favorite texture class
#include <UGKGLTexture.h>
#include <UGKAlgebra.h>
#include <stdio.h>

#ifdef MODEL_API_ASSIMP
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>
#endif

// A VERY simple vector struct
// I could have included a complex class but I wanted the model class to stand alone
typedef UGK::UGKALG_SimpleVector M3DS_Vector;

// Color struct holds the diffuse color of the material
struct Color4i{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

// Holds the material info
// TODO: add color support for non textured polys
struct Material{
	UGKS_String name;	// The material's name
	GLTextureV tex;	// The texture (this is the only outside reference in this class)
	bool textured;	// whether or not it is textured
	Color4i color;
};

// I sort the mesh by material so that I won't have to switch textures a great deal
struct MaterialFaces{
	unsigned short *subFaces;	// Index to our vertex array of all the faces that use this material
	int numSubFaces;			// The number of faces
	int MatIndex;				// An index to our materials
};

// The 3ds file can be made up of several objects
struct Object{
	UGKS_String name;				// The object name
	float *Vertexes;			// The array of vertices
	float *Normals;				// The array of the normals for the vertices
	float *TexCoords;			// The array of texture coordinates for the vertices
	unsigned short *Faces;		// The array of face indices
	int numFaces;				// The number of faces
	int numMatFaces;			// The number of differnet material faces
	int numVerts;				// The number of vertices
	int numTexCoords;			// The number of vertices
	bool textured;				// True: the object has textures
	MaterialFaces *MatFaces;	// The faces are divided by materials
	M3DS_Vector pos;					// The position to move the object to
	M3DS_Vector rot;					// The angles to rotate the object
};

/**
	@class Model_3DS

   * Loads, holds and draws a 3D model

*/

class UGK_API Model_3DS
{
protected:
#ifdef MODEL_API_ASSIMP
	static Assimp::Importer importer;
	const aiScene* scene;
#endif

	UGKS_String ModelName,		// The name of the model
			Path;			// The path of the model

public:
	
	int numObjects;			// Total number of objects in the model
	int numMaterials;		// Total number of materials in the model
	int totalVerts;			// Total number of vertices in the model
	int totalFaces;			// Total number of faces in the model
	bool shownormals;		// True: show the normals
	Material *Materials;	// The array of materials
	Object *Objects;		// The array of objects in the model
	M3DS_Vector pos,		// The position to move the model to
				rot,		// The angles to rotate the model
				scale;		// The size you want the model scaled to
	bool lit;				// True: the model is lit
	bool visible;			// True: the model gets rendered
	
	Model_3DS();			// Constructor
	virtual ~Model_3DS();	// Destructor
	
	/**
	 * Load a model 
	 * Supports all common 3d model formats
	 * .3ds, .dae, .blend, .ms3d, etc.
	 * For a detailed list, see http://assimp.sourceforge.net/main_features_formats.html
	 *
	 */
	void Load();
	
	/**
	 * Draw the model 
	 */
	void Draw();

	//Setters
	inline void SetModelName(UGKS_String MN)	{ModelName = MN;}		// Set the name of the model
	inline void SetPath		(UGKS_String P)		{ Path = P; }

	//Getters
	inline UGKS_String GetModelName	() { return ModelName; }		// Get the name of the model
	inline UGKS_String GetPath		() { return Path; }

private:
	/** 
	 * Calculates the normals of the vertices by averaging
	 * the normals of the faces that use that vertex
	*/
	void CalculateNormals();
};

#endif MODEL_3DS_H