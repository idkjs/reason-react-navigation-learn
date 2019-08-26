open ReactNative;
open ReactNavigation;
type counter = {
  count: int,
  decrement: unit => unit,
  increment: unit => unit,
};

let useState = initial => {
  React.useReducer((_, action) => action, initial);
};

let useCounter = (~initialState=0, ()) => {
  let (count, setCount) = useState(initialState);
  let decrement = () => setCount(count - 1);
  let increment = () => setCount(count + 1);
  {count, decrement, increment};
};

module Counter =
  UnstatedNext.CreateContainer({
    type state = int;
    type value = counter;
    let useHook = useCounter;
  });
module CounterDisplay = {
  [@react.component]
  let make = () => {
    let counter = Counter.useContainer();
    <View
      style=Style.(
        style(~flex=1., ~alignItems=`center, ~justifyContent=`center, ())
      )>
      <View style=Style.(style(~width=100.->dp, ~height=50.->dp, ()))>
        <Button title="-" onPress={_ => counter.decrement()} />
      </View>
      <Text style=Style.(style(~fontSize=50., ()))>
        {React.string(string_of_int(counter.count))}
      </Text>
      <View style=Style.(style(~width=100.->dp, ~height=50.->dp, ()))>
        <Button title="+" onPress={_ => counter.increment()} />
      </View>
    </View>;
  };
};

module HomeScreen = {
  [@react.component]
  let make = () =>
    <Counter.Provider>
      <CounterDisplay />
      <Counter.Provider initialState=2> <CounterDisplay /> </Counter.Provider>
    </Counter.Provider>;
};

module AppContainer =
  AppContainer.Make({
    type screenProps = {. "someProp": int};
    let routes = {
      "Home": {
        screen: HomeScreen.make,
      },
    };
    let defaultNavigationOptions = {
      "headerTintColor": "#fff",
      "headerStyle": Style.(style(~backgroundColor="#f4511e", ())),
      "headerTitleStyle": Style.(style(~fontWeight=`bold, ())),
    };
    let configOptions = StackUtils.config(~defaultNavigationOptions, ());
    let navigator = StackNavigator.(makeWithConfig(routes, configOptions));
  });

[@react.component]
let make = () => <AppContainer />;