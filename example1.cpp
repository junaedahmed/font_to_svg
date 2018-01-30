// main.cpp font_to_svg - public domain
#include <iostream>
#include <fstream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "font_to_svg.hpp"

std::stringstream debug;

int main( int argc, char * argv[] )
{
	if (argc!=3) {
		std::cerr << "usage: " << argv[0] << " file.ttf\n";
		exit( 1 );
	}

	std::string filename;
	FT_Library library;
	FT_Face face;
	FT_Error error;
	filename = argv[1];

	error = FT_Init_FreeType( &library );
	// debug << "Init error code: " << error;

	// Load a typeface
	error = FT_New_Face( library, filename.c_str(), 0, &face );
	// debug << "\nFace load error code: " << error;
	// debug << "\nfont filename: " << filename;
	if (error) {
		std::cerr << "problem loading file " << filename << "\n";
		exit(1);
	}
	// debug << "\nFamily Name: " << face->family_name;
	// debug << "\nStyle Name: " << face->style_name;
	// debug << "\nNumber of faces: " << face->num_faces;
	// debug << "\nNumber of glyphs: " << face->num_glyphs;


	std::string line;
	std::string file = argv[2];
	std::ifstream f (file);
	while(getline(f, line)) {
		std::cout << &line;
		std::cout << line;
		std::string gln = line;
	    FT_String * gname = new char[gln.size() + 1];
	    std::copy(gln.begin(), gln.end(), gname);
	    gname[gln.size()] = '\0';
	    FT_UInt gindex = FT_Get_Name_Index(face, gname);
	    delete[] gname;
	    font2svg::glyph g( argv[1], gindex);
		std::ofstream myf (gln + ".svg", std::ios::out);
		myf << g.svgheader();
		myf << g.svgtransform();
		myf << g.outline();
		myf << g.svgfooter();
		g.free();
		myf.close();
	}

	
	

  return 0;
}
