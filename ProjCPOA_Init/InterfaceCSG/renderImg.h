#ifndef RENDERIMG_H
#define RENDERIMG_H

#include <QGLWidget>
#include <QTimer>

#include "../image/Img2DGrey.h"
#include "../image/imgGradient.h"
#include "../vectorMatrix/ProjectVectors.h"
#include "../csg/BoundingBox.h"
//#include "particle.h"


struct errorHandling
{
    static GLenum glCheckError_(const char *file, int line)
    {
        GLenum errorCode;
        while ((errorCode = glGetError()) != GL_NO_ERROR)
        {
            std::string error;
            switch (errorCode)
            {
                case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
                case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
                case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
                case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
                case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
                case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
                case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            }
            std::cerr << error << " | " << file << " (" << line << ")" << std::endl;
        }
        return errorCode;
    }
};

#define glCheckError() errorHandling::glCheckError_(__FILE__, __LINE__)


class RenderImg : public QGLWidget
{
	Q_OBJECT

	QTimer *m_timer;

public:
    RenderImg(BoundingBox& bb, QWidget *parent = 0);
	~RenderImg();

	void loadTexture(const std::string& filename);
	void updateDataTexture();

    Img2DGrey& getImg();
	unsigned int getWidth();
	unsigned int getHeight();

	/**
	 * @brief clean image
	 */
	void clean();


   /**
	* @brief update sobel image
	*/
   void toggleSobel();

   /**
	* @brief setif BB has to be drawn
	* @param v
	*/
   void setBBDraw(bool v) { m_BBdraw = v;}

protected slots:
	void animate();

protected:
	/// Qt callbacks
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);


	/// transform win coordinate in texel image coordinate
	void coordInTexture(QMouseEvent *event, int& x, int& y);

	/// transform img coord to GL [-1,+1]
	inline float xImg2GL(float x)
	{
		return -1.0f + (2.0f*x)/float(m_widthTex-1);
	}

	/// transform img coord to GL [-1,+1]
	inline float yImg2GL(float y)
	{
        return 1.0f - (2.0f*y)/float(m_heightTex-1); // minus because of GL is bottom to up and image up to boytom
	}



	/// Texture information
	GLuint m_texture;
	int m_widthTex;
	int m_heightTex;
	unsigned char* m_ptrTex;

	/// GL Widget sizes
	int m_winW;
	int m_winH;
	int m_winS;

	/// for mouse move
	QPoint m_lastPos;
	/// key modifier state (shift/ctrl/...)
	int m_state_modifier;

	bool m_drawSobel;

	bool m_BBdraw;
    BoundingBox& m_BB;


	void drawBB(const BoundingBox& bb);

	void drawSobel();

//	ici les declaration de:
//   - l'image a niveau de gris
//	 - l'image gradiant'
    Img2DGrey m_img;
    Img2D<Vec2D> m_grad;
    imgGradient gradient;

//	 la fontaine de particule
//	Fountain fountain;
};

#endif // RENDERIMG_H
