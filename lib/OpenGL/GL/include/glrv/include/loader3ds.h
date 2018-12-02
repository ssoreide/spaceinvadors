#ifndef LOADER3DS_H
#define LOADER3DS_H
// 3D Studio Model Class
// by: Matthew Fairfax
//

#include <stdio.h>

class Model_3DS
{
public:
    // A VERY simple vector struct
    // I could have included a complex class but I wanted the model class to stand alone
    struct Vector {
        float x;
        float y;
        float z;
    };

    // Vertex struct to make code easier to read in places
    struct Vertex {
        float x;
        float y;
        float z;
    };

    // Color struct holds the diffuse color of the material
    struct Color4i {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };

    // Holds the material info
    // TODO: add color support for non textured polys
    struct Material {
        char name[80];	// The material's name
        unsigned char* tex;	// The texture (this is the only outside reference in this class)
        bool textured;	// whether or not it is textured
        Color4i color;
    };

    // Every chunk in the 3ds file starts with this struct
    struct ChunkHeader {
        unsigned short id;	// The chunk's id
        unsigned long  len;	// The lenght of the chunk
    };

    // I sort the mesh by material so that I won't have to switch textures a great deal
    struct MaterialFaces {
        unsigned short *subFaces;	// Index to our vertex array of all the faces that use this material
        int numSubFaces;			// The number of faces
        int MatIndex;				// An index to our materials
    };

    // The 3ds file can be made up of several objects
    struct Object {
        char name[80];				// The object name
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
        Vector pos;					// The position to move the object to
        Vector rot;					// The angles to rotate the object
    };

    char *modelname;		// The name of the model
    char *path;				// The path of the model
    int numObjects;			// Total number of objects in the model
    int numMaterials;		// Total number of materials in the model
    int totalVerts;			// Total number of vertices in the model
    int totalFaces;			// Total number of faces in the model
    bool shownormals;		// True: show the normals
    Material *Materials;	// The array of materials
    Object *Objects;		// The array of objects in the model
    Vector pos;				// The position to move the model to
    Vector rot;				// The angles to rotate the model
    float scale;			// The size you want the model scaled to
    bool lit;				// True: the model is lit
    bool visible;			// True: the model gets rendered
    void Load(char *name);	// Loads a model
//	void Draw();			// Draws the model
    void Extent(float &xmin, float &xmax, float &ymin, float &ymax, float &zmin, float &zmax) const;
    void LoadTexture(char * name);
    FILE *bin3ds;			// The binary 3ds file
    Model_3DS();			// Constructor
    virtual ~Model_3DS();	// Destructor

private:
    void IntColorChunkProcessor(long length, long findex, int matindex);
    void FloatColorChunkProcessor(long length, long findex, int matindex);
    // Processes the Main Chunk that all the other chunks exist is
    void MainChunkProcessor(long length, long findex);
        // Processes the model's info
        void EditChunkProcessor(long length, long findex);

            // Processes the model's materials
            void MaterialChunkProcessor(long length, long findex, int matindex);
                // Processes the names of the materials
                void MaterialNameChunkProcessor(long length, long findex, int matindex);
                // Processes the material's diffuse color
                void DiffuseColorChunkProcessor(long length, long findex, int matindex);
                // Processes the material's texture maps
                void TextureMapChunkProcessor(long length, long findex, int matindex);
                    // Processes the names of the textures and load the textures
                    void MapNameChunkProcessor(long length, long findex, int matindex);

            // Processes the model's geometry
            void ObjectChunkProcessor(long length, long findex, int objindex);
                // Processes the triangles of the model
                void TriangularMeshChunkProcessor(long length, long findex, int objindex);
                    // Processes the vertices of the model and loads them
                    void VertexListChunkProcessor(long length, long findex, int objindex);
                    // Processes the texture cordiantes of the vertices and loads them
                    void TexCoordsChunkProcessor(long length, long findex, int objindex);
                    // Processes the faces of the model and loads the faces
                    void FacesDescriptionChunkProcessor(long length, long findex, int objindex);
                        // Processes the materials of the faces and splits them up by material
                        void FacesMaterialsListChunkProcessor(long length, long findex, int objindex, int subfacesindex);

    // Calculates the normals of the vertices by averaging
    // the normals of the faces that use that vertex
    void CalculateNormals();
};
#endif // LOADER3DS_H
