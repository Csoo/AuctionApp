Hálózati kommunikációra a 3rdparty mappában találhtaó httplib.h-t használja

Hálózati kommunikáció json alapon valósul meg, hozzá QtJson mosdulokat használ (nlohmann::json helyett)

A projekt cmake alapú, server implementáció a server mappában, teljes funkcionlitás implementációja a main-ben

Docker:
A server mappájából (innen): 

    docker image build -t auctionapp:latest .

    docker container run -it auctionapp

megjegyzés: azért 19.10-es ubuntu, mert ezt 2. alkalomra hibátlanul build-elte, 18.10-től az összes többi min 5x elszállt repo hiba miatt
    
