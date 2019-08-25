
open ReactNative;
external unsafeCast: ReactNavigation.NavigationOptions.t => 'a = "%identity";
open ReactNavigation;

module LogoTitle = {
  [@react.component]
  let make = () => {
    <Image
      source=Image.Source.fromRequired(Packager.require("./assets/spiro.png"))
      style=Style.(style(~width=30.->dp, ~height=30.->dp, ()))
    />;
  };
};
module TestButton = {
  [@react.component]
  let make = () => {
    // <Button onPress={_e => Js.log("Example button pressed")} title="Example button" />;
    <Button title="Info"
        color="#fff" onPress={_e =>
          Alert.alert(~title="This is a button!", ());
        }
      />
  };
};
module HomeScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    let param = {"itemId": 86, "otherParam": "anything you want here"};
    <View
      style=Style.(
        style(~flex=1., ~alignItems=`center, ~justifyContent=`center, ())
      )>
      <Text> {"Home Screen" |> React.string} </Text>
      <Button
        title="Go to Details"
        onPress={_ =>
          navigation->Navigation.navigateWithParams("Details", param)
        }
      />
    </View>;
  };
  make->NavigationOptions.(setNavigationOptions(t(
      ~headerTitle=NavigationOptions.HeaderTitle.element(<LogoTitle />),
      ~headerRight=<TestButton />,
      // ~headerRight=<Button title="Info"
      //   color="#fff" onPress={_e =>
      //     Alert.alert(~title="This is a button!", ());
      //   }
      // />,
     ())));
};
module DetailsScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {

    let itemId =
      navigation->Navigation.getParamWithDefault("itemId", "NO-ID");

    let otherParam =
      navigation->Navigation.getParamWithDefault(
        "otherParam",
        "some default value",
      );

    <View
      style=Style.(
        style(~flex=1., ~alignItems=`center, ~justifyContent=`center, ())
      )>
      <Text> {"Details Screen" |> React.string} </Text>
      <Text> {"itemId: " ++ itemId |> React.string} </Text>
      <Text> {"otherParam: " ++ otherParam |> React.string} </Text>
      <Button
        title="Go to Details... again"
        onPress={_ =>
          navigation->Navigation.navigateWithParams(
            "Details",
            {
              "itemId": [%bs.raw {| String(Math.floor(Math.random() * 100)) |}],
            },
          )
        }
      />
      <Button
        title="Go to Home"
        onPress={_ => navigation->Navigation.navigate("Home")}
      />
      <Button
        title="Update the title"
        onPress={_ =>
          navigation->NavUtils.setParams({"otherParam": "Updated!"})
        }
      />
      <Button title="Go back" onPress={_ => navigation->Navigation.goBack} />
    </View>;
  };
  make->NavigationOptions.setDynamicNavigationOptions(params => {
    let navigation = params##navigation;
    let navigationOptions = params##navigationOptions;

    let navigationOptions = unsafeCast(navigationOptions);

    let navigationOptionsheaderTintColor = navigationOptions##headerTintColor;
    let navigationOptionsheaderStylebackgroundColor =
      navigationOptions##headerStyle##backgroundColor;

    let newHeaderTintColor = navigationOptionsheaderStylebackgroundColor;

    let newHeaderStyle: ReactNative.Style.t =
      Style.(style(~backgroundColor=navigationOptionsheaderTintColor, ()));

    let title =
      navigation->Navigation.getParamWithDefault(
        "otherParam",
        "A Nested Details Screen",
      );

    NavigationOptions.t(
      ~title,
      ~headerStyle=newHeaderStyle,
      ~headerTintColor=newHeaderTintColor,
      (),
    );
  });
};

module RootStack = {
  let routes = {
    "Home": {
      screen: HomeScreen.make,
    },
    "Details": {
      screen: DetailsScreen.make,
    },
  };
};

module AppContainer =
  AppContainer.Make({
    type screenProps = {. "someProp": int};
    let routes = RootStack.routes;
    let defaultNavigationOptions = {
      "headerTintColor": "#fff",
      "headerStyle": Style.(style(~backgroundColor="#f4511e", ())),
      "headerTitleStyle": Style.(style(~fontWeight=`bold, ())),
    };
    let configOptions =
      StackUtils.config(
        ~initialRouteName="Home",
        ~defaultNavigationOptions,
        (),
      );
    let navigator = StackNavigator.(makeWithConfig(routes, configOptions));
  });

[@react.component]
let make = () => <AppContainer />;