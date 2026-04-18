#include "logistics.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

/*class Product*/

Product::Product(int id, string n, string c, double w, double p) : productId(id), name(n),category(c), weight(w), price(p) {}

int Product::getId() const { return productId; }
string Product::getName() const { return name; }
double Product::getWeight() const { return weight; }
double Product::getPrice() const { return price; }
vector<int> Product::getComponents() const { return componentIds; }

/*class Client*/

Client::Client(int id, const string& n, const string& c) : clientId(id), name(n), city(c) {}

int Client::getId() const { return clientId; }
string Client::getName() const { return name; }
string Client::getCity() const { return city; }
vector<int> Client::getVectorOrdersId() const { return vectorOrdersId; }

int Client::addOrder(int ord1) {
    if (ord1<1) return -1;
    for (int id : vectorOrdersId) {
        if (ord1 == id) return 1; }
 
    vectorOrdersId.push_back(ord1);
    return 0;
}
/*class warehouse*/

Warehouse::Warehouse(int id, const string& c) : warehouseId(id), city(c) {}
Warehouse::Warehouse(int id, const string& c, vector<pair<Product*,int>> vpq) : warehouseId(id), city(c),vectorPQ(vpq) {}

int Warehouse::getId() const { return warehouseId; }
string Warehouse::getCity() const { return city; }
vector<pair<Product*,int>> Warehouse::getVectorPQ() const { return vectorPQ; }
int Warehouse::addProduct(int prodId, int quant, ProductManagement& PrManager) {

    if (quant <= 0)
        return -1;

    Product* prod = nullptr;

    for (auto p : PrManager.getVectorProducts()) {
        if (p->getId() == prodId) {
            prod = p;
            break;
        }
    }

    if (prod == nullptr)
        return -1;
    // procurar produto no vetor
    for (auto &pq : vectorPQ) {
        if (pq.first->getId() == prodId) {
            pq.second += quant;   // atualizar quantidade
            return 1;
        }
    }

    vectorPQ.push_back(make_pair(prod, quant));

    return 0;
}
/*class order*/

Order::Order(int id, Client* cl, Warehouse* war, string dat) : orderId(id), client(cl), warehouse(war), date(dat) {}

int Order::getId() const { return orderId ;}
Client* Order::getClient() const { return client; }
Warehouse* Order::getWarehouse() const { return warehouse; }
vector<ProdQuan*> Order::getVectorProducts() const { return productQuant; }

int Order::addProduct(Product *prod, int quant) {
    if (prod==nullptr || quant<1) return -1;
    for (ProdQuan* pq : productQuant) {
        if (pq->product == prod) return 1; }
    ProdQuan *p=new ProdQuan(prod,quant);
    productQuant.push_back(p);
    return 0;
}

/*class ClientManagement*/

ClientManagement::ClientManagement(){ vectorClients.clear();};
ClientManagement::~ClientManagement(){
    while(vectorClients.size()!=0)
       {

	  	
            delete (vectorClients[vectorClients.size()-1]);
            vectorClients.pop_back();
                
       } 
    }


vector<Client*> ClientManagement::getVectorClients() const { return vectorClients; }

int ClientManagement::clientInsert(Client* cli) {
   if (cli==nullptr) return -1;
    for (auto it = vectorClients.begin(); it != vectorClients.end(); ++it) {
        if ((*it) == cli) {
            return 1;
        }
    }
    vectorClients.push_back(cli);
    return 0; 

}


/*class ProductManagement*/
ProductManagement::ProductManagement(){ vectorProducts.clear();};
ProductManagement::~ProductManagement(){
    while(vectorProducts.size()!=0)
       {

	  	
            delete (vectorProducts[vectorProducts.size()-1]);
            vectorProducts.pop_back();
                
       } 
    }


vector<Product*> ProductManagement::getVectorProducts() const { return vectorProducts; }

int ProductManagement::productInsert(Product* prod) {
   if (prod==nullptr) return -1;
    for (auto it = vectorProducts.begin(); it != vectorProducts.end(); ++it) {
        if ((*it) == prod) {
            return 1;
        }
    }
    vectorProducts.push_back(prod);
    return 0; 

}

/*class WarehouseManagement*/
WarehouseManagement::WarehouseManagement(){ vectorWarehouses.clear();};
WarehouseManagement::~WarehouseManagement(){
    while(vectorWarehouses.size()!=0)
       {

	  	
            delete (vectorWarehouses[vectorWarehouses.size()-1]);
            vectorWarehouses.pop_back();
                
       } 
    }


vector<Warehouse*> WarehouseManagement::getVectorWarehouses() const { return vectorWarehouses; }

int WarehouseManagement::warehouseInsert(Warehouse* ware) {
   if (ware==nullptr) return -1;
    for (auto it = vectorWarehouses.begin(); it != vectorWarehouses.end(); ++it) {
        if ((*it) == ware) {
            return 1;
        }
    }
    vectorWarehouses.push_back(ware);
    return 0; 

}

/*class OrderManagement*/
OrderManagement::OrderManagement(){ vectorOrders.clear();};
OrderManagement::~OrderManagement(){
    while(vectorOrders.size()!=0)
       {

	  	
            delete (vectorOrders[vectorOrders.size()-1]);
            vectorOrders.pop_back();
                
       } 
    }


vector<Order*> OrderManagement::getVectorOrders() const { return vectorOrders; }

int OrderManagement::orderInsert(Order* ord) {
   if (ord==nullptr) return -1;
    for (auto it = vectorOrders.begin(); it != vectorOrders.end(); ++it) {
        if ((*it) == ord) {
            return 1;
        }
    }
    vectorOrders.push_back(ord);
    return 0; 

}

/**************************/
/*     A implementar      */
/**************************/


int Product::addComponent(int compId, ProductManagement& ProdManagement) {
  return 2;
  //responder aqui;
}

void Product::displayProductInfo(ostream& o) const {
 //responder aqui;
}

int Product::ChecktotalWeight(ProductManagement& ProdManagement) const {
   return 2;
    //responder aqui;
}


int OrderManagement::updateOrders(string filename, ClientManagement& ClManager, ProductManagement& PrManager, WarehouseManagement& WareManager) {
    return 2;
    //responder aqui;
}

vector<string> WarehouseManagement::WarehouseWihtProduct(int productId) {
  
    return {};
        //responder aqui;
}