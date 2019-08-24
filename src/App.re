open ReactNative;
open ReactNavigation;

module HomeScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    <Screen name="Home Screen">
      <Button
        title="Go to Details"
        onPress={_ => navigation->Navigation.navigate("Details")}
      />
    </Screen>;
  };
};
module DetailsScreen = {
  [@react.component]
  let make = () => {
    <Screen name="Details Screen" />;
  };
};
module RootStack = {
  let navigator =
    StackNavigator.(
      make({
        "Home": HomeScreen.make,
        "Details": DetailsScreen.make,
        "initialRouteName": "Details",
      })
    );
};

module AppContainer =
  AppContainer.Make({
    type screenProps = {. "someProp": int};

    // let navigator = AppNavigator.navigator;
    // using shorthand
    // There is no `initialScreenName config on `StackNavigator` in reason.
    // the initial screen is the first item in you array, here `Home`. Flip them around to see `Details` rendered first
    // let navigator =
    //   StackNavigator.(
    //     make({
    //       "Home": HomeScreen.make,
    //       "Details": DetailsScreen.make,
    //       "initialRouteName":"Details"
    //     })
    //   );
    // Reason version of https://snack.expo.io/@react-navigation/hello-react-navigation-v3 and https://reactnavigation.org/docs/en/hello-react-navigation.html#summary
    let navigator = RootStack.navigator;
  });
[@react.component]
let app = () => {
  let screenProps = {"someProp": 42};
  <AppContainer screenProps />;
};