#include "NonPerishable.h"
//edited by Cebile Nxumalo
NonPerishable::NonPerishable(int productID,string name,double price,int quantity,double taxRate,double discountRate)
      :Product(productID, name, price, taxRate, discountRate)
{
    //ctor
}

NonPerishable::~NonPerishable()
{
    //dtor
}
