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
  let make = (~navigation: Navigation.t) => {
    <Screen name="Details Screen">
      <Button
        title="Go to Details Screen Again"
        // js version: `onPress={() => this.props.navigation.push('Details')}`
        // `navigate` doesnt go anywhere because you are already on this page
        //  `push` in js, lets you indicate that you want to go to that screen anyway.
        onPress={_ => navigation->Navigation.navigate("Details")}
      />
      <Button title="Go back" onPress={_ => navigation->Navigation.goBack} />
      <Button
        title="Go to Home"
        onPress={_ => navigation->Navigation.navigate("Home")}
      />
      //  `popToTop` take you to the top route in the current stack so this will go back to `Home` route..
      <Button
        title="PopToTop"
        onPress={_ => navigation->Navigation.popToTop}
      />
    </Screen>;
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