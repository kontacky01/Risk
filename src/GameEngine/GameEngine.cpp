class State {
    string name;
}
class Transition {
    string command;
    string initial state;
    string final state;
}
State currentState;


init() {


    initialState = new State("start")
        mapLoadedState = new State("mapLoaded")
        initialState = new State("start")
        initialState = new State("start")
        initialState = new State("start")

        currentState = initialState;

    t1 = new Transition(initialState, "loadMap", mapLoadedState)
        t2 = new Transition(loadMapState, "loadMap", ...)
        t3 = new Transition(initialState, "loadMap", mapLoadedState)

}

vector of transitions


while (currentState != endState) {
    //in the loop i only use vector of transitions here
    // take command
    // if combination of state + command is valid -> go to new state
}
// user enters command
// i save it in  strin
GameEngineDriver{
    //this is where i call the init() function
}