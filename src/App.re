open ReactNative;
open ReactNavigation;

module HomeScreen = {
  [@react.component]
  let make = () => {
    <Screen name="Home Screen" />;
  };
};
module DetailsScreen = {
  [@react.component]
  let make = () => {
    <Screen name="Details Screen" />;
  };
};
module AppContainer =
  AppContainer.Make({
    type screenProps = {. "someProp": int};

    // let navigator = AppNavigator.navigator;
    // using shorthand
    // There is no `initialScreenName config on `StackNavigator` in reason.
    // the initial screen is the first item in you array, here `Home`. Flip them around to see `Details` rendered first
    let navigator =
      StackNavigator.(
        make({
          "Home": HomeScreen.make,
          "Details": DetailsScreen.make,
        })
      );
  });
[@react.component]
let app = () => {
  let screenProps = {"someProp": 42};
  <AppContainer screenProps />;
};