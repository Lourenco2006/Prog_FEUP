#include "logistics.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <stack>

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
vector<pair<Product*,int>>& Warehouse::getVectorPQUpdate() { return vectorPQ; }
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



int Product::addComponent(int compId, ProductManagement& ProdManagement) {
    if (compId == productId) return -1;
    for (int id : componentIds)
        if (id == compId) return 1;
    bool test=false;
    double w;
    for (Product* prod: ProdManagement.getVectorProducts()) {
        if (compId==prod->getId()) {
            test=true;
            w=prod->getWeight();
            break;
            }

    }
    if (!test) return -1;
    componentIds.push_back(compId);
    if (componentIds.size()==1) { 
            weight=w; 
        } 
        else {
        weight+=w; 
        }
    return 0;
}

void Product::displayProductInfo(ostream& o) const {
    o << productId << " | " << name << " | " << category << " | " << weight << " | " << price ;
   
    if (componentIds.size()>0) {o <<   " | Components: ";}
    for (int id : componentIds) o << id << " ";
    o << endl;
}

int Product::ChecktotalWeight(ProductManagement& ProdManagement) const {
    double soma=0.0;
    if (componentIds.size()==0) {
        return 1;
    } else {
        for (int cmp:componentIds){ 
            for (Product* prod: ProdManagement.getVectorProducts()) {
                if (cmp==prod->getId()) {
                    soma=soma+prod->getWeight();
                    break;
                }
            }
        }
        if (soma==weight) {
            return 1;
        } else return 0;
    }
    return 0;
}


int OrderManagement::updateOrders(string filename, ClientManagement& ClManager, ProductManagement& PrManager, WarehouseManagement& WareManager) {
    ifstream file(filename);
   
    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return -1;
    }
    int total=0;
    string line;
    bool existClient=false;
    bool existWarehouse=false;
  //  bool existOrder=false;
    bool existProduct=false;
    Client* cli1;
    Warehouse *ware1;
    Product* prod1;
    while (getline(file, line)) {
        stringstream ss(line);
        int ordId, cliId,wareId,prodId, quant;
        string dat,str;
        
        getline(ss, str, ';');
        ordId = stoi(str);
        getline(ss, str, ';');
        cliId = stoi(str);
        getline(ss, str, ';');
        wareId = stoi(str);
        getline(ss, dat, ';');
        
        //existOrder=false;
        for (Order * ord: getVectorOrders()){
            if (ordId==ord->getId()){
                continue;
            }
        }
       

         existWarehouse=false;
        for (Warehouse * ware: WareManager.getVectorWarehouses()){
            if (wareId==ware->getId()){
                existWarehouse=true;
                ware1=ware;
            }
        }
        if (!existWarehouse) { continue;}
        

        existClient=false;
        for (Client * cli: ClManager.getVectorClients()){
            if (cliId==cli->getId()){
                existClient=true;
                cli1=cli;
            }
        }
        if (!existClient) { continue;}
        Order *ord = new Order(ordId,cli1,ware1,dat);

        while(getline(ss, str, ';')) {
         prodId = stoi(str);
         getline(ss, str, ';');   
         quant = stoi(str); 
          existProduct=false;
        for (Product * prod: PrManager.getVectorProducts()){
            if (prodId==prod->getId()){
                existProduct=true;
                prod1=prod;
            }
        }
        if (!existProduct) { continue;}   

        ord->addProduct(prod1,quant);


        }
       orderInsert(ord);
       cli1->addOrder(ordId);
    total++;
    }
    file.close();
   
    return total; 
}

vector<string> WarehouseManagement::WarehouseWihtProduct(int productId) {
    vector<string> vec;
     
    Product* prod;
   // vector<Product*> vp;
   // vector<int> vq;
    vector<pair<Product*,int>> vpq;
    for (Warehouse* ware : vectorWarehouses) {
       
     //   vp=ware->getVectorProducts();
     //   vq=ware->getQuantProducts();
        vpq=ware->getVectorPQ();
        for (size_t i=0;i<vpq.size();i++) {
            prod=vpq[i].first;

            if (prod->getId()==productId && vpq[i].second>0 ) {
              
                vec.push_back(ware->getCity());
            }
        }
    }

   
    sort(vec.begin(), vec.end());
    

   
    return vec;
}

Shipment::Shipment(int id, Order* ord, string st, string dd, string deld)
    : shipmentId(id), order(ord), status(st), dispatchDate(dd), deliveryDate(deld) {}

int Shipment::getId() const { return shipmentId; }
Order* Shipment::getOrder() const { return order; }
string Shipment::getStatus() const { return status; }
string Shipment::getDispatchDate() const { return dispatchDate; }
string Shipment::getDeliveryDate() const { return deliveryDate; }

ShipmentManagement::ShipmentManagement() {}

ShipmentManagement::~ShipmentManagement() {
    while (!listShipments.empty()) {
        delete listShipments.front();
        listShipments.pop_front();
    }
}

list<Shipment*> ShipmentManagement::getListShipments() const {
    return listShipments;
}

queue<Order*> ShipmentManagement::getPendingOrders() const {
    return queuePendingOrders;
}

stack<string> ShipmentManagement::getStackOperations() const {
    return stackOperations;
}

int ShipmentManagement::shipmentInsert(Shipment* ship) {
    if (ship == nullptr) return -1;

    for (Shipment* s : listShipments) {
        if (s->getId() == ship->getId())
            return 1;
    }

    listShipments.push_back(ship);
    return 0;
}

int ShipmentManagement::addPendingOrder(Order* ord) {
    if (ord==nullptr)
        return -1;
    for (queue<Order*> tempQueue = queuePendingOrders; !tempQueue.empty(); tempQueue.pop()) {
        if (tempQueue.front() == ord)            return 1;
    }
    queuePendingOrders.push(ord);
    return 0;
}

void ShipmentManagement::addStockOperation(string op) {
    stackOperations.push(op);
}



int ShipmentManagement::uploadShipments(string filename, OrderManagement& OrdManager) {
    ifstream file(filename);
    if (!file.is_open()) return -1;

    int total = 0;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string str;
        int shipId, orderId;
        string status, dispatchDate, deliveryDate;

        getline(ss, str, ';');
        shipId = stoi(str);

        getline(ss, str, ';');
        orderId = stoi(str);

        getline(ss, status, ';');
        getline(ss, dispatchDate, ';');
        getline(ss, deliveryDate, ';');

        Order* ord = nullptr;
        for (Order* o : OrdManager.getVectorOrders()) {
            if (o->getId() == orderId) {
                ord = o;
                break;
            }
        }

        if (ord == nullptr) continue;

        Shipment* ship = new Shipment(shipId, ord, status, dispatchDate, deliveryDate);

        if (shipmentInsert(ship) == 0) {
            total++;

            if (status == "pending")
                queuePendingOrders.push(ord);
        }
        else {
            delete ship;
        }
    }

    file.close();
    return total;
}

/**************************/
/*     A implementar      */
/**************************/

int ShipmentManagement::numberOrdersInQueue(int minProducts) {
    queue<Order*>PO = this->queuePendingOrders;

    if(this->queuePendingOrders.empty() || minProducts<0)
        return -1;

    int count = 0;
    while(!PO.empty())
    {

        if(PO.front()->getVectorProducts().size() >= (size_t)minProducts)
        count++;

        PO.pop();
    }

    return count;
}

int ShipmentManagement::numberDeliveredOnDate(string date) {
    
    if(date.empty() || date.length() != 10 )
    return -1;
   
    int count = 0;
   
    for(auto it = this->listShipments.begin(); it != this->listShipments.end();it++)
    {
        if((*it)->getDeliveryDate() == date && (*it)->getStatus() == "delivered")
        {
            count++;
        }
    }
    
    return count;
}

string ShipmentManagement::mostReturnedProduct(int &num) {
    num = 0;
   
    vector<string> prodvec;
    vector<int>contagens;
    for(auto it = this->listShipments.begin(); it != this->listShipments.end();it++)
    {
        if((*it)->getStatus()=="returned" && (*it)->getOrder() != nullptr)
        {
            const auto &products = (*it)->getOrder()->getVectorProducts();
           
            for(size_t i = 0;i < products.size();i++)
            {
               string nome = products[i]->product->getName();
               int q = products[i]->quantity;
               bool encontrado = false;
               
               for(size_t j = 0; j < prodvec.size(); j++)
                 {
                   if(prodvec[j] == nome)
                   {
                       contagens[j]+= q;
                       encontrado = true;
                       break;
                   }
               }
               
               if(!encontrado)
               {
                   prodvec.push_back(nome);
                   contagens.push_back(q);
                   
               }
           }
       }
   }
   
   int max = 0;
   string product = "";
   
   for(size_t i = 0;i<prodvec.size();i++)
   {
       if(contagens[i]>max)
        { 
            max=contagens[i];
            product=prodvec[i];
        }
        else if(contagens[i] == max)
        {
            if(prodvec[i]<product)
                product=prodvec[i];
        }
       
   }
   num = max;
   return product;
 
}

int ShipmentManagement::undoLastStockOperation(WarehouseManagement& WareManager, ProductManagement& PrManager) {
    
    if(this->stackOperations.empty())
    return -1;
   
    string o,x,y,z;
   
    stringstream ss;
   
    ss<<this->stackOperations.top();
    this->stackOperations.pop();
    getline(ss,o,' ');
    getline(ss,x,' ');
    getline(ss,x,' ');
    getline(ss,x,' ');
    getline(ss,y,' ');
    getline(ss,y,' ');
    getline(ss,z,' ');
    getline(ss,z,' ');
    
    Warehouse* w = nullptr;
    pair<Product*,int>* pq = nullptr;
    
    for(size_t i = 0; i < WareManager.getVectorWarehouses().size();i++)
    {
        if(WareManager.getVectorWarehouses()[i]->getId() == stoi(x))
        {
            w = WareManager.getVectorWarehouses()[i];
            break;
        }
    }
    
    if( w == nullptr)
    return -1;
    
    int a = 0;
    
    for(size_t j = 0; j < w->getVectorPQUpdate().size(); j++)
    {
        if(w->getVectorPQUpdate()[j].first->getId() == stoi(y) )
        {
            pq = &w->getVectorPQUpdate()[j];
            a = j;
            break;
        }
    }
    

    if(o == "ADD")
    {
        if( pq == nullptr)
        return -1;
    
        pq->second = pq->second-stoi(z);
        
        if(pq->second<=0)
        {
            w->getVectorPQUpdate().erase(w->getVectorPQUpdate().begin()+a);
        }
        
    }
    
    else if(o == "REMOVE")
    {
        if(pq != nullptr)
        {
             if(pq->second<0)
                pq->second = 0;
        
             if(pq->second >= 0)
            {
                pq->second += stoi(z);
            }
        
        }
        
        else if(pq == nullptr)
        {
            Product* PP = nullptr;
            
            for(size_t i = 0; i < PrManager.getVectorProducts().size(); i++)
            {
                if(PrManager.getVectorProducts()[i]->getId() == stoi(y))
                {
                    PP = PrManager.getVectorProducts()[i];
                    break;
                }
            }
            
            if(PP == nullptr)
            return -1;
            
            w->getVectorPQUpdate().push_back(make_pair(PP,stoi(y)));
        }
        
    }
    
    return 0;
    
}

vector<string> ShipmentManagement::productsWithNotEnoughStock(WarehouseManagement& WareManager) 
{
   
   queue<Order*> qo = this->queuePendingOrders;
   vector<string> pi;
   
   while(!qo.empty())
   {
       auto p = qo.front()->getVectorProducts();
       
       for(size_t j = 0; j < p.size();j++)
       {
           
          for(size_t i = 0; i < WareManager.getVectorWarehouses().size();i++)
          {
              for(size_t k = 0; k< WareManager.getVectorWarehouses()[i]->getVectorPQ().size();k++)
              {
                  bool found = false;
                  for(size_t l = 0; l< pi.size(); l++)
                  {
                       if(p[j]->product->getName() == pi[l])
                       {
                           found = true;
                       }
                  }
                  if(p[j]->product->getName() == WareManager.getVectorWarehouses()[i]->getVectorPQ()[k].first->getName() && !found)
                         {
                             if(p[j]->quantity > WareManager.getVectorWarehouses()[i]->getVectorPQ()[k].second )
                                {
                                pi.push_back(p[j]->product->getName());
                                }                         
                        }
                 
              }
          }
       }

        qo.pop();
     }
       

    return pi;
}
   
  

