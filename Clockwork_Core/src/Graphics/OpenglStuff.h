#pragma once

namespace clockwork {
	namespace graphics {

		/*hexadecimal value of the type in opengl*/
		template<typename GLtype>
		struct OpenglType
		{
			static const int gltype = 0;
		};
		template<>
		struct OpenglType<float>
		{
			static const int gltype = 0x1406;
		};
		template<>
		struct OpenglType<double>
		{
			static const int gltype = 0x140A;
		};
		template<>
		struct OpenglType<char>
		{
			static const int gltype = 0x1400;
		};
		template<>
		struct OpenglType<unsigned char>
		{
			static const int gltype = 0x1401;
		};
		template<>
		struct OpenglType<short>
		{
			static const int gltype = 0x1402;
		};
		template<>
		struct OpenglType<unsigned short>
		{
			static const int gltype = 0x1403;
		};
		template<>
		struct OpenglType<int>
		{
			static const int gltype = 0x1404;
		};
		template<>
		struct OpenglType<unsigned int>
		{
			static const int gltype = 0x1405;
		};

		/*must be called from the render thread with an active opengl context( Window::init() has to be called first and then atleast one window object has to be created before calling this method)
		has to be called before using any buffer and it will initialize the internal copy buffers | will be called from the engine constructor
		@param[size] the reserved size in bytes for the private copy buffers of the buffer classes*/
		void initBuffers(unsigned int size) noexcept;

		/*must be called from the render thread with an active opengl context( Window::init() has to be called first and then atleast one window object has to be created before calling this method)
		should be called before using any opengl relatted stuff, because it will enable opengl blending, culling, depth test 

		Face Culling: back side of models/textures are not rendered(only those that face the viewer) 50% more performance for the fragment shader | for example: from a cube not more than 3 faces can face viewer at the same time
		@param[cullFace] the faces to cull(not draw) | GL_FRONT = 1028 GL_BACK = 1029 GL_FRONT_AND_BACK = 1032 | the default is GL_BACK to only render the front facing faces and culling the faces that are not facing the viewer | GL_FRONT would render the insides of a model
		@param[windingOrder] the drawing order of the vertices to identify the faces that are facing the viewer(front facing) | GL_CW = 2304 GL_CCW = 2305 | the default is cw to render the front faces as clockwise order of the vertices
		the vertices of a model should be in (default clockwise) the order from the viewers perspective when directly looking at them(the viewer has to move around the model for the other sides) | when looking at a model, the vertices on the other side facing the inside of the model will not be rendered, because they will automaticly be in a diffrent order
		counter clockwise order is for right coordinate hand system and clockwise order for left hand coordinate system

		Depth testing: only draw the closest fragments to the viewer and discard fragments further away at the same screen position(is done in screen space after fragment shader has run and stencil testing has run but before the projection matrix is applied) | also early depth testing before the fragment shader is possible if you dont write to the fragments depth value in the shader
		the fragment position will be accessed in the range -1 to 1 with the z component being the depth value | can be accessed in the shader via gl_FragCoord.xyz | the depth value is from 0.0 to 1.0 and its the distance from the model to the viewer (1/z-1/near)/(far-near)
		objects should not be placed too close together because of z-fighting(flickering between the 2 models when the z values are equal, or too close) | so its best to always add a small offset between the objects thats not visible to the user
		@param[depthCompare] the compare method how fragments are processed and which fragments will be visible at the screen
		GL_ALWAYS = 519 the depth test always passes, so the last rendered fragment will be visible at the screen | GL_NEVER = 512 the depth test never passes and maybe only the first fragment will be visible at the sscreen
		GL_LESS = 513 passes if the depth value is less than the stored depth value, so the nearest fragment will be visible at the screen  
		GL_GREATER = 516 passes if the depth value is greater than the stored depth value, so the farthest fragment will be visible at the screen 
		GL_EQUAL = 514 passes if the depth value is equal to the stored depth value | GL_NOTEQUAL = 517 passes if tthe depth value is not equal to the stored depth value 
		GL_LEQUAL = 515 less or equal: this is the default to render the closest models over the other models, but render later drawn models over existing ones | GL_GEQUAL = 518 greater or equal
		
		Blending: implementing transparency within objects(colour is combination of colours of all objects and not a solid colour), so you can see through objects(for example coloured glass) | this is defined by the alpha value between 0 to 1 for the 4. colour component of a pixel
		an alpha value of 1 would mean no transparency and nothing behind the object is visible, but an alpha value of 0.5 would mean 50% of the own colour and 50% of the colours behind the object will be mixed
		fragments with a very low alpha value should be discarded in the fragment shader for full transparency | blending will happen after the fragment shader
		blending will mix the colours: resultColour = sourceColour * sourceFactor + bufferColour * bufferFactor | sourceColour is the colour of the fragment of the current texture, bufferColour is the colour of the fragment stored in the colour buffer at that position | the factors set the impact of the alpha value on the colour
		@param[blendSourceFactor] the factor applied to the sourceColour | default is GL_SRC_ALPHA to multiply the colour by the alpha value and should be used for standard transparency along with the other default parameter
		@param[blendDestinationFactor] the factor applied to the bufferColour | default is GL_SRC_1_MINUS_SRC_ALPHA to multiply the colour by the remaining alpha value for a combined transparency | the rgb and alpha channels can also be set individually by using glBlendFuncSeparate
		GL_ZERO = 0 factor is equal to zero | GL_ONE = 1 factor is equal to one | GL_SRC_COLOR = 768 factor is source colour | GL_ONE_MINUS_SRC_COLOR = 769 factor is 1 minus source colour | GL_DST_COLOR = 774 | GL_ONE_MINUS_DST_COLOR = 769
		GL_SRC_ALPHA = 770 factor is the alpha component of the source colour | GL_DST_ALPHA = 772
		GL_SRC_ONE_MINUS_SRC_ALPHA = 771 factor is 1 minus the alpha component of the source colour | GL_ONE_MINUS_DST_ALPHA = 773
		GL_CONSTANT_COLOR = 32769 factor is the constant colour vector | GL_ONE_MINUS_CONSTANT_COLOR = 32770 | GL_CONSTANT_ALPHA = 32771 | GL_ONE_MINUS_CONSTANT_ALPHA = 32772
		@param[blendFunc] the kind of function used to calculate the colour | default is GL_FUNC_ADD = 32774 | GL_FUNC_SUBSTRACT = 32778 | GL_FUNC_REVERSE_SUBSTRACT = 32779*/
		void openglParams(int cullFace = 1029, int windingOrder = 2304, int depthCompare = 515, int blendSourceFactor = 770, int blendDestinationFactor= 771, int blendFunc = 32774) noexcept;

		/*kommentieren | erstellt immoment nur framebuffers in texturearray2d | auch in texturearray2d bei friend deklaration kommentieren*/
		void initTextures();

	}
}