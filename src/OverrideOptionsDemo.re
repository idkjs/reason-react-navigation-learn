open ReactNative;

open ReactNavigation;

// create a dummy screen to pass something to `AppContainer`
module ExampleScreen = {
  [@react.component]
  let make = () => {
    <Screen name="Example Screen" />;
  };
};
module Home = {
  // define the routes seperately for readability
  let routes = {
    "Feed": {
      screen: ExampleScreen.make,
    },
    "Profile": {
      screen: ExampleScreen.make,
    },
  };

    // define the defaultNavigationOptions seperately for readability

  let defaultNavigationOptions = {
    "title": "Home",
    "headerTintColor": "#fff",
    "headerStyle": Style.(style(~backgroundColor="#000", ())),
  };
  // `tabBarLabel` is represented in the binding as `title` as far as I can tell. There is a `TabBarLabel` module  but I can not get it to pass in this format yet. Instead, I used the `setNavigationOptions` method from the bindings found here: https://github.com/reasonml-community/reason-react-native/blob/21a72c601c12adaf09ebd0cd55d57ecb59a650f8/reason-react-navigation/src/NavigationOptions.re#L165 which is having the desired effect apparently.

  // use StackUtils version of `StackNavigator.config` which has the `defaultNavigationOptions` option available on it.
  let configOptions =
    StackUtils.config(
      ~defaultNavigationOptions,
      (),
    );

  // pass the `routes` and `config` to our `StackNavigator`
  let navigator = StackNavigator.(makeWithConfig(routes, configOptions));
  // use `setNavigationOptions` to create the title per the demo. See notes above on `tabBarLabel`. The `title` property here overrides the `tabBarLabel` title, not the `title` we set in `defaultNavigationOptions`.
  navigator->NavigationOptions.setNavigationOptions(
    NavigationOptions.t(~title="Home!", ()),
  );
};
// same as below, longer version to emulate the demo here: https://reactnavigation.org/docs/en/headers.html#overriding-shared-navigationoptions
// module Tabs = {
//   let navigator = TabNavigator.Bottom.(make({"Home": Home.navigator}));
// };
// module AppContainer =
//   AppContainer.Make({
//     type screenProps = {. "someProp": int};
//     let navigator = Tabs.navigator;
//   });
module AppContainer =
  AppContainer.Make({
    type screenProps = {. "someProp": int};
      let navigator = TabNavigator.Bottom.(make({"Home": Home.navigator}));
  });

[@react.component]
let make = () => <AppContainer />;