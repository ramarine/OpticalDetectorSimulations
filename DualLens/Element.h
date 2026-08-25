#ifndef __ELEMENT__
#define __ELEMENT__

class Element {

 public:
  int m_id;

   Element(int id): m_id( id ) {;}

  int getId() const { return m_id; }


};
#endif 
