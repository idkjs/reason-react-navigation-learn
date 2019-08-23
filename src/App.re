open ReactNative;
open ReactNavigation;
module HomeScreen = {
  open Expo;

  let styles =
    Style.(
      StyleSheet.create({
        "container":
          style(
            ~flex=1.,
            ~justifyContent=`center,
            ~alignItems=`center,
            ~backgroundColor="#F5FCFF",
            (),
          ),
        "instructions": style(~textAlign=`center, ~color="#ffffff", ()),
      })
    );

  [@react.component]
  let make = () => {
    <View style=styles##container>
      <LinearGradient
        colors=[|"#DD4B39", "#C62C19"|]
        start=[|0.0, 0.0|]
        _end=[|1.0, 1.0|]
        style=Style.(style(~padding=dp(12.), ~borderRadius=12., ()))>
        <Text style=styles##instructions>
          {React.string("Home Screen")}
        </Text>
      </LinearGradient>
    </View>;
  };
};
// module AppNavigator = {
//   let routes = {"Home": HomeScreen.make};

//   let navigator = StackNavigator.(make(routes));
// };
module AppContainer =
  AppContainer.Make({
    type screenProps = {. "someProp": int};

    // let navigator = AppNavigator.navigator;
    // using shorthand
    let navigator = StackNavigator.(make({"Home": HomeScreen.make}));
  });
[@react.component]
let app = () => {
  let screenProps = {"someProp": 42};
  <AppContainer screenProps />;
};