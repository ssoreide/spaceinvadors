/***************************************************
Funciones de utilidad de shaderss para OpenGL 2.1 
Roberto Viv�, 2012 (v1.0)

Dependencias: 
+GLEW.h,GLUT.h
+glew32.lib,GLUT32.lib,glew32.dll,GLUT32.dll
***************************************************/

#ifndef RV_SHADERS
#define RV_SHADERS

#include <GL/GLEW.h>								//Librer�a de extensiones a OpenGL 2.1
#include <GL/GLUT.h>								//Librer�a de utilidades estandar sobre OpenGL

GLuint buildShader(const char* shaderFile, GLenum stype);
/* Carga c�digo GLSL desde un fichero de texto, lo compila y devuelve el
identificador. Escribe por consola y en el fichero "error.log" para debug.
Par�metros:
	-shaderFile: Nombre de fichero fuente GLSL
	-stype: GL_VERTEX_SHADER | GL_FRAGMENT_SHADER seg�n el tipo de shader
*/

GLuint buildProgramShader(const char* shaderFile, GLenum stype);
/* Construye un programa listo para usar si todo va bien con un s�lo shader de
v�rtice o fragmento en c�digo fuente GLSL. Devuelve el identificador si no
se producen errores. Usa el fichero "error.log" para escribir errores.
Par�metros:
	-shaderFile: Nombre del fichero fuente GLSL del shader
	-stype: GL_VERTEX_SHADER | GL_FRAGMENT_SHADER seg�n el tipo de shader
*/

GLuint buildProgramShaders(const char* vShaderFile, const char* fShaderFile);
/* Construye un programa listo para usar si todo va bien con los shaders de
v�rtice y fragmento en c�digo fuente GLSL. Devuelve el identificador si no
se producen errores. Usa el fichero "error.log" para escribir errores.
Par�metros:
	-vShaderFile: Nombre del fichero fuente GLSL del shader de v�rtices
	-fShaderFile: Nombre del fichero fuente GLSL del shader de fragmentos
*/

#endif