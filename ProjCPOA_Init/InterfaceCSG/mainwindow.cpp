#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include"csgPrimitive.h"

#include <QFileDialog>
#include <QTextCursor>

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
    m_currentNode(NULL),
    m_prim(NULL),
    m_oper(NULL),
	m_graphTextEdit(NULL),
	m_stopSignal(false)

{
	ui->setupUi(this);

    //m_render = new RenderImg();
    m_render = new RenderImg(this->m_bb);

	ui->HLayout->insertWidget(0,m_render,99);
	m_render->setFocusPolicy(Qt::ClickFocus);

	ui->translationX->setMinimum(-100);
	ui->translationX->setMaximum(100);
	ui->translationY->setMinimum(-100);
	ui->translationY->setMaximum(100);
	
	ui->scale->setMinimum(-100);
	ui->scale->setMaximum(100);
	
	ui->currentNode->setMaximum(0);
	ui->id_filsGauche->setMaximum(0);
	ui->id_filsDroit->setMaximum(0);
	
	connect(ui->create_oper,SIGNAL(clicked()),SLOT(createOperation()));
	connect(ui->create_prim,SIGNAL(clicked()),SLOT(createPrimtive()));
	connect(ui->resetTransfo,SIGNAL(clicked()),SLOT(resetTransfo()));
	connect(ui->applyTransfo,SIGNAL(clicked()),SLOT(applyTransfo()));

	connect(ui->translationX,SIGNAL(valueChanged(int)),SLOT(transfoSliderChanged()));
	connect(ui->translationY,SIGNAL(valueChanged(int)),SLOT(transfoSliderChanged()));
	connect(ui->rotation,SIGNAL(valueChanged(int)),SLOT(transfoSliderChanged()));
	connect(ui->scale,SIGNAL(valueChanged(int)),SLOT(transfoSliderChanged()));

	connect(ui->dsb_tx,SIGNAL(valueChanged(double)),SLOT(transfoSpinChanged()));
	connect(ui->dsb_ty,SIGNAL(valueChanged(double)),SLOT(transfoSpinChanged()));
	connect(ui->dsb_Rot,SIGNAL(valueChanged(double)),SLOT(transfoSpinChanged()));
	connect(ui->dsb_s,SIGNAL(valueChanged(double)),SLOT(transfoSpinChanged()));

	connect(ui->actionLoadIMG, SIGNAL(triggered()), this, SLOT(loadImage()));
	connect(ui->actionSaveIMG, SIGNAL(triggered()), this, SLOT(saveImage()));
	connect(ui->actionDrawSobel, SIGNAL(triggered()), this, SLOT(drawSobel()));

	connect(ui->actionLoadCSG, SIGNAL(triggered()), this, SLOT(loadCSG()));
	connect(ui->actionSaveCSG, SIGNAL(triggered()), this, SLOT(saveCSG()));
	connect(ui->actionAppendCSG, SIGNAL(triggered()), this, SLOT(appendCSG()));
	connect(ui->actionClearCSG, SIGNAL(triggered()), this, SLOT(clearCSG()));

	connect(ui->actionClone, SIGNAL(triggered()), this, SLOT(clone()));
	connect(ui->actionSwapLRRoot, SIGNAL(triggered()), this, SLOT(swapLRRoot()));
	connect(ui->actionUnjoinRoot, SIGNAL(triggered()), this, SLOT(unjoinRoot()));

	connect(ui->currentNode, SIGNAL(valueChanged(int)), this, SLOT(currentNodeChanged(int)));
	connect(ui->checkBox_drawCurrent, SIGNAL(toggled(bool)), this, SLOT(updateTreeRender()));

	connect(ui->id_filsGauche, SIGNAL(valueChanged(int)), this, SLOT(updateTreeRender()));
	connect(ui->id_filsDroit, SIGNAL(valueChanged(int)), this, SLOT(updateTreeRender()));


	m_graphTextEdit = new GraphTextEdit();
	m_graphTextEdit->show();
	connect(m_graphTextEdit,SIGNAL(copyAvailable(bool)),SLOT(nodeTextSelected(bool)));
	update();
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::updateTreeRender()
{
	drawTree();
	m_render->update();
}



void MainWindow::closeEvent(QCloseEvent* /*event*/)
{
	m_graphTextEdit->close();
}

void MainWindow::createPrimtive()
{
	int prim =  ui->prim_type->currentIndex();
	int sides = ui->nb_sides->value();
    CsgDisk* newDisk;
    CsgRegularPolygon* newPoly;
    CsgNode* newNode = NULL;

// VOTRE CODE ICI : primitive creation
    switch(prim)
    {
        case 0 :
            newDisk = new CsgDisk();
            newNode = dynamic_cast<CsgNode*>(newDisk);
            break;
        case 1:
            newPoly = new CsgRegularPolygon(sides);
            newNode = dynamic_cast<CsgNode*>(newPoly);
            break;
    }

    m_tree.addPrimitive(newNode);
    m_currentNode = newNode;
    std::cerr << newNode->getId() << std::endl;

    updateTreeRender();
    ui->currentNode->setValue(newNode->getId()); // recupere l'id du noeud cree
	updateTextGraph();

}


void MainWindow::createOperation()
{
	int typeOp = ui->Operation->currentIndex();
	int left = ui->id_filsGauche->value();
	int right = ui->id_filsDroit->value();

	std::cout << "createOperation  ";
    std::cout << "type: "<< typeOp;
	std::cout << " child: "<< left << " & "<< right;
	std::cout << std::endl;

    CsgOperation* oper=NULL;
	switch(typeOp)
	{
        case 0:
            oper = m_tree.joinPrimitives(left, right, op_union);
			break;
        case 1:
            oper = m_tree.joinPrimitives(left, right, op_inter);
			break;
        case 2:
            oper = m_tree.joinPrimitives(left, right, op_diff);
			break;
		default:
            std::cerr << "unknown operation. Valid operations are : 0 -> union, 1 -> intersection, 2 -> difference." << std::endl;
			return;
			break;
	};

    if (oper == NULL)
        return;

// mettre a jour ui->currentNode ui->id_filsGauche ui->id_filsDroit

    m_transfo = Matrix33D::identity();
    m_current_center = oper->BBox.getCenter();
    m_currentNode = oper;

// mettre a jour ui->currentNode ui->id_filsGauche ui->id_filsDroit
    ui->currentNode->setValue(oper->getId());
    ui->id_filsGauche->setValue(left);
    ui->id_filsDroit->setValue(right);

	updateTreeRender();

	updateTextGraph();

}


void MainWindow::applyTransfo()
{

    m_transfo = m_currentNode->getTransformationMatrix();

    if(dynamic_cast<CsgOperation*>(m_currentNode) != NULL)
    {
        dynamic_cast<CsgOperation*>(m_currentNode)->applyLocalTransformation();
    }
    else if(dynamic_cast<CsgDisk*>(m_currentNode) != NULL)
    {
        dynamic_cast<CsgDisk*>(m_currentNode)->applyLocalTransformation();
    }
    else if(dynamic_cast<CsgRegularPolygon*>(m_currentNode) != NULL)
    {
        dynamic_cast<CsgRegularPolygon*>(m_currentNode)->applyLocalTransformation();
    }

    m_currentNode->setTransformationMatrix(Matrix33D::identity());
	resetTransfoWidgets();
	updateTreeRender();
}


void MainWindow::resetTransfoWidgets()
{
	m_stopSignal=true;
	ui->translationX->setValue(0);
	ui->translationY->setValue(0);
	ui->scale->setValue(0);
	ui->rotation->setValue(0);
	m_stopSignal=false;
	transfoSliderChanged();

}


void MainWindow::resetTransfo()
{
    m_currentNode->setTransformationMatrix(m_transfo);
	resetTransfoWidgets();
}

void MainWindow::transfoChanged()
{
	// recupere la primitive courante et lui applique les transformations
	// VOTRE CODE ICI
    //m_transfo = m_currentNode->getTransformationMatrix();
    m_transfo = m_currentNode->getTransformationMatrix();
    m_transfo.addScale(ui->dsb_s->value(), ui->dsb_s->value());
    m_transfo.rotate(ui->dsb_Rot->value());
    m_transfo.translate(ui->dsb_tx->value(), ui->dsb_ty->value());
    m_transfo = m_transfo * m_currentNode->getInversedTransformationMatrix();
    m_currentNode->setTransformationMatrix(m_transfo);

//    if(dynamic_cast<CsgOperation*>(m_currentNode) != NULL)
//    {
//        dynamic_cast<CsgOperation*>(m_currentNode)->applyLocalTransformation();
//    }
//    else if(dynamic_cast<CsgDisk*>(m_currentNode) != NULL)
//    {
//        dynamic_cast<CsgDisk*>(m_currentNode)->applyLocalTransformation();
//    }
//    else if(dynamic_cast<CsgRegularPolygon*>(m_currentNode) != NULL)
//    {
//        dynamic_cast<CsgRegularPolygon*>(m_currentNode)->applyLocalTransformation();
//    }

	updateTreeRender();
}

#define S1_FACTOR 20.0
#define S2_FACTOR 40.0


void MainWindow::transfoSliderChanged()
{
	if (m_stopSignal)
		return;

	m_stopSignal = true;

	ui->dsb_tx->setValue(ui->translationX->value());
	ui->dsb_ty->setValue(ui->translationY->value());
	ui->dsb_Rot->setValue(ui->rotation->value());

	int ss = ui->scale->value();
	if (ss>=0)
		ui->dsb_s->setValue(1.0+ss/S1_FACTOR);
	else
		ui->dsb_s->setValue(1.0/(1.0-ss/S2_FACTOR));

    transfoChanged();

	m_stopSignal = false;

}

void MainWindow::transfoSpinChanged()
{
	if (m_stopSignal)
		return;

	m_stopSignal = true;

	ui->translationX->setValue(ui->dsb_tx->value());
	ui->translationY->setValue(ui->dsb_ty->value());
	ui->rotation->setValue(ui->dsb_Rot->value());

	double ss = ui->dsb_s->value();
	if (ss>=1.0)
		ui->scale->setValue((ss-1.0)*S1_FACTOR);
	else
		ui->scale->setValue((1.0-1.0/ss)*S2_FACTOR);

	m_stopSignal = false;

	transfoChanged();
}

#undef S1_FACTOR
#undef S2_FACTOR


void MainWindow::loadImage()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), QDir::currentPath(),tr("pgm (*.pgm);;all (*.*)"));
	if (!fileName.isEmpty())
	{
		std::string strFN = fileName.toStdString();

        std::ifstream in(strFN.c_str());
        if (!in.good())
        {
            std::cerr << "Unable to open file " << strFN << std::endl;
            return;
        }

		// load texture
		m_render->loadTexture(strFN);
		update();
	}
}

void MainWindow::saveImage()
{
	QString fileName = QFileDialog::getSaveFileName(this,
									tr("Save Image"), QDir::currentPath(),tr("pgm (*.pgm);;all (*.*)"));
	if (!fileName.isEmpty())
	{
		std::string strFN = fileName.toStdString();

        std::ifstream in(strFN.c_str());
        if (!in.good())
        {
            std::cerr << "Unable to open file " << strFN << std::endl;
            return;
        }

        m_render->getImg().saveImageToPGMFile(strFN);
	}
}


void MainWindow::drawSobel()
{
	m_render->toggleSobel();
}


void MainWindow::loadCSG()
{
    CsgOperation* op;
	QString fileName = QFileDialog::getOpenFileName(this,
									tr("Open File"), QDir::currentPath(),tr("csg (*.csg);;all (*.*)"));
	if (!fileName.isEmpty())
	{
		std::string strFN = fileName.toStdString();

		std::ifstream in(strFN.c_str());
		if (!in.good())
		{
			std::cerr << "Unable to open file " << strFN << std::endl;
			return;
		}

	// VOTRE CODE ICI
        m_tree.clear();
        m_tree << strFN;

		 updateTextGraph();
         updateTreeRender();

// mettre a jour ui->currentNode ui->id_filsGauche ui->id_filsDroit ui->currentNode
         auto it = m_tree.treesList.begin();
         ++it;
         ui->currentNode->setValue(it->first);

         if((op = dynamic_cast<CsgOperation*>(ui->currentNode)) != NULL)
         {
             ui->id_filsGauche->setValue(op->leftChild->getId());
             ui->id_filsDroit->setValue(op->rightChild->getId());
         }
         else
         {
             ui->id_filsDroit->setValue(0);
             ui->id_filsGauche->setValue(0);
         }
	}
}

// same as load but no clear before readind the tree
void MainWindow::appendCSG()
{
    CsgOperation* op;
	QString fileName = QFileDialog::getOpenFileName(this,
									tr("Open File"), QDir::currentPath(),tr("csg (*.csg);;all (*.*)"));
	if (!fileName.isEmpty())
	{
		std::string strFN = fileName.toStdString();

	// VOTRE CODE ICI
        std::ifstream in(strFN.c_str());
        if (!in.good())
        {
            std::cerr << "Unable to open file " << strFN << std::endl;
            return;
        }

    // VOTRE CODE ICI
        m_tree << strFN;

        // mettre a jour ui->currentNode ui->id_filsGauche ui->id_filsDroit ui->currentNode
         auto it = m_tree.treesList.begin();
         ++it;
         ui->currentNode->setValue(it->first);

         if((op = dynamic_cast<CsgOperation*>(ui->currentNode)) != NULL)
         {
             ui->id_filsGauche->setValue(op->leftChild->getId());
             ui->id_filsDroit->setValue(op->rightChild->getId());
         }
         else
         {
             ui->id_filsDroit->setValue(0);
             ui->id_filsGauche->setValue(0);
         }


		 updateTextGraph();
		updateTreeRender();
	}
}

void MainWindow::saveCSG()
{
	QString fileName = QFileDialog::getSaveFileName(this,
									tr("Save File"), QDir::currentPath(),tr("csg (*.csg);;all (*.*)"));
	if (!fileName.isEmpty())
	{
		std::string strFN = fileName.toStdString();

        std::ifstream in(strFN.c_str());
        if (!in.good())
        {
            std::cerr << "Unable to open file " << strFN << std::endl;
            return;
        }

	// VOTRE CODE ICI
        m_tree >> strFN;
	}
}

void MainWindow::clearCSG()
{
    m_tree.clear();
	updateTextGraph();
	updateTreeRender();
// mettre a jour ui->currentNode ui->id_filsGauche ui->id_filsDroit ui->currentNode
    ui->currentNode->setValue(0);
    ui->id_filsDroit->setValue(0);
    ui->id_filsGauche->setValue(0);
}


void MainWindow::clone()
{
    CsgOperation* op;
   m_currentNode =  m_tree.clone(m_currentNode->getId());

	updateTextGraph();
	updateTreeRender();

// mettre a jour ui->currentNode ui->id_filsGauche ui->id_filsDroit ui->currentNode
    ui->currentNode->setValue(m_currentNode->getId());
    if((op = dynamic_cast<CsgOperation*>(m_currentNode)) != NULL)
    {
        ui->id_filsGauche->setValue(op->leftChild->getId());
        ui->id_filsDroit->setValue(op->rightChild->getId());
    }
    else
    {
        ui->id_filsDroit->setValue(0);
        ui->id_filsGauche->setValue(0);
    }
}


void MainWindow::drawTree()
{
	m_render->clean();

    Img2DGrey temp(m_render->getHeight(), m_render->getWidth());
    m_render->getImg() = temp;
    m_tree.drawInImage( m_render->getImg() );

    if (ui->checkBox_drawCurrent->isChecked() && m_currentNode!=NULL)
	{
		// OPTION: trace le noeud courant dans l'image de m_render
		// VOTRE CODE ICI

		m_render->setBBDraw(true);
        m_bb = m_currentNode->BBox;
        m_tree.drawInImage(m_currentNode, m_render->getImg(), 125);
	}
	else
	{
		m_render->setBBDraw(false);
	}

// trace les 2 fils de l'operation avec 2 niveau de gris pour vizu
//    int idf = ui->id_filsGauche->value();
//	if (idf != 0)
//	{
//        auto fNode = m_tree.nodesList.find(idf);
//        if ((fNode != m_tree.nodesList.end()) && (dynamic_cast<CsgOperation*>(fNode->second) != NULL ))
//            m_tree.drawInImage(fNode->second, m_render->getImg(),175);
//	}

//	idf = ui->id_filsDroit->value();
//	if (idf != 0)
//	{
//        auto fNode = m_tree.nodesList.find(idf);
//        if ((fNode != m_tree.nodesList.end()) && (dynamic_cast<CsgOperation*>(fNode->second) != NULL ))
//            m_tree.drawInImage(fNode->second, m_render->getImg(),200);
//	}

	m_render->updateDataTexture();
    //std::cout << m_render->getImg() << std::endl;
}


void MainWindow::nodeTextSelected(bool sel)
{
	if (!sel)
		return;

	QTextCursor cursor = m_graphTextEdit->textCursor();
	std::string nodeLabel = cursor.selectedText().toStdString();

	if (nodeLabel.size() !=5)
		return;

	// get id from label string
	std::string strId = nodeLabel.substr(2,4);
	std::stringstream ss(strId);
	unsigned int id;
	ss >> id;

	ui->currentNode->setValue(id);

	if (m_graphTextEdit->pressed() == 'l')
	{
		ui->id_filsGauche->setValue(id);
	}
	else if (m_graphTextEdit->pressed() == 'r'	)
	{
		ui->id_filsDroit->setValue(id);
	}
	else
	{
		ui->currentNode->setValue(id);
	}

}


void MainWindow::updateTextGraph()
{
	// update Graph in TextWindow
	m_graphTextEdit->clear();
//	std::string str = m_tree.asciiArtGraph();
//	m_graphTextEdit->appendPlainText(str.c_str());
}


void MainWindow::currentNodeChanged(int id)
{
    CsgOperation* op;
    auto it = m_tree.nodesList.find(id);

    if(it != m_tree.nodesList.end())
    {
        m_currentNode = it->second;

        if((op = dynamic_cast<CsgOperation*>(m_currentNode)) != NULL)
        {
            ui->id_filsGauche->setValue(op->leftChild->getId());
            ui->id_filsDroit->setValue(op->rightChild->getId());
        }
        else
        {
            ui->id_filsDroit->setValue(0);
            ui->id_filsGauche->setValue(0);
        }
    }

	resetTransfoWidgets();

}


void MainWindow::swapLRRoot()
{
// VOTRE CODE ICI
    CsgOperation* op;
    CsgNode* temp;

    if((op = dynamic_cast<CsgOperation*>(m_currentNode)) != NULL)
    {
        temp = op->leftChild;
        op->leftChild = op->rightChild;
        op->rightChild = temp;

        ui->id_filsGauche->setValue(op->leftChild->getId());
        ui->id_filsDroit->setValue(op->rightChild->getId());
    }


	updateTextGraph();
	updateTreeRender();
}



void MainWindow::unjoinRoot()
{
// VOTRE CODE ICI

    CsgOperation* op;

    if((op = dynamic_cast<CsgOperation*>(m_currentNode)) != NULL)
    {
        m_tree.removeNode(op);
    }

    m_currentNode = NULL;
    ui->currentNode = 0;
    ui->id_filsGauche->setValue(0);
    ui->id_filsDroit->setValue(0);

	updateTextGraph();
	updateTreeRender();
}


GraphTextEdit::GraphTextEdit()
{
	this->resize(800,800);
	this->setWindowTitle("CSG-Graph");
	this->setReadOnly(true);
	this->setWordWrapMode(QTextOption::NoWrap);

	QFont font = QFont ("Courier");
	font.setStyleHint(QFont::TypeWriter);
	font.setPointSize(11);
	font.setFixedPitch (true);
	this->setFont(font);
}

