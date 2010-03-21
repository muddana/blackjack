//right now is dummy channel write to io but need to use some client/server communication to route messages to different clients
class ServerChannel{
public:
  void write(string  message){
    cout << message << endl;
  };
  string read(){
    string temp = "";
    cin >> temp;
    return temp;
  };
};
