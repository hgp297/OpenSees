/* ****************************************************************** **
**    OpenSees - Open System for Earthquake Engineering Simulation    **
**          Pacific Earthquake Engineering Research Center            **
**                                                                    **
**                                                                    **
** (C) Copyright 1999, The Regents of the University of California    **
** All Rights Reserved.                                               **
**                                                                    **
** Commercial use of this program without express permission of the   **
** University of California, Berkeley, is strictly prohibited.  See   **
** file 'COPYRIGHT'  in main directory for information on usage and   **
** redistribution,  and for a DISCLAIMER OF ALL WARRANTIES.           **
**                                                                    **
** Developed by:                                                      **
**   Frank McKenna (fmckenna@ce.berkeley.edu)                         **
**   Gregory L. Fenves (fenves@ce.berkeley.edu)                       **
**   Filip C. Filippou (filippou@ce.berkeley.edu)                     **
**                                                                    **
** ****************************************************************** */
                                                                        
// $Revision: 1.4 $
// $Date: 2002-12-16 21:10:00 $
// $Source: /usr/local/cvs/OpenSees/SRC/element/beam3d/beam3d02.h,v $
                                                                        
                                                                        
// File: ~/model/beam3d02.h
//
// Written: fmk 11/95
// Revised:
//
// Purpose: This file contains the class definition for beam3d02.
// beam3d02 is a plane frame member.

#ifndef beam3d02_h
#define beam3d02_h

#include <Element.h>
#include <Node.h>
#include <Matrix.h>
#include <Vector.h>

class Channel;

class beam3d02 : public Element
{
  public:
    beam3d02();        
    beam3d02(int tag, double A, double E, double G, 
	      double Jx, double Iy, double Iz, int Nd1, int Nd2, double theta);
    ~beam3d02();

    int getNumExternalNodes(void) const;
    const ID &getExternalNodes(void);
    Node **getNodePtrs(void);

    int getNumDOF(void);
    void setDomain(Domain *theDomain);

    int revertToLastCommit(void);        
    
    const Matrix &getTangentStiff(void);
    const Matrix &getInitialStiff(void);

    void zeroLoad(void);	
    int addLoad(ElementalLoad *theLoad, double loadFactor);
    int addInertiaLoadToUnbalance(const Vector &accel);

    const Vector &getResistingForce(void);
    const Vector &getResistingForceIncInertia(void);            
    
    int sendSelf(int commitTag, Channel &theChannel);
    int recvSelf(int commitTag, Channel &theChannel, FEM_ObjectBroker &theBroker);
    
    void Print(ostream &s, int flag =0);    
    
  private:
    const Matrix &getStiff(void);    
    void formVar(void);
    
    double A,E,G,Jx,Iy,Iz,theta;
    double L;
    double dx,dy,dz,EA,twoE,fourE,twelveE,sixE;
    
    static Matrix k; // the stiffness matrix
    static Matrix m; // the mass matrix	
    static Matrix d; // the damping matrix
	
    Vector rForce;
    Vector load;
    
    ID  connectedExternalNodes;    
    int isStiffFormed;
    Node *theNodes[2];
};

#endif


