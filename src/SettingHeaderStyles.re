open ReactNative;

open ReactNavigation;
module HomeScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    // trying this to see if we can work towards json serializable values to use with deeplinking as mentioned here: https://reactnavigation.org/docs/en/params.html
    let param = {"itemId": 86, "otherParam": "anything you want here"};
    // Js.log2("TEST", Js.Json.test(param, Object)); // true
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

  make->NavigationOptions.setNavigationOptions(
    NavigationOptions.t(
      ~headerTitleStyle=Style.(style(~fontWeight=`bold, ())),
      ~headerTintColor="#fff",
      ~headerStyle=Style.(style(~backgroundColor="#f4511e", ())),
      ~title="Home",
      (),
    ),
  );
  // alternativelt, define the prop and pass it to `NavigationOptions`
  // let headerStyle = Style.(style(~backgroundColor="#f4511e", ()));
  // let headerTitleStyle = Style.(style(~fontWeight=`bold, ()));
  // let headerTintColor = "#fff";
  // make->NavigationOptions.setNavigationOptions(
  //   NavigationOptions.t(
  //     ~headerTitleStyle,
  //     ~headerTintColor,
  //     ~headerStyle,
  //     ~title="Home",
  //     (),
  //   ),
  // );
};

module DetailsScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    // in reason-react-native you have to use `navigateWithParams` to get be able to use the default value behaviour shown in the example here: https://reactnavigation.org/docs/en/params.html
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
    let title =
      params##navigation
      ->Navigation.getParamWithDefault(
          "otherParam",
          "A Nested Details Screen",
        );
    NavigationOptions.t(~title, ());
  });
};
module RootStack = {
  let navigator =
    StackNavigator.(
      make({"Home": HomeScreen.make, "Details": DetailsScreen.make})
    );
};

module AppContainer =
  AppContainer.Make({
    type screenProps = {. "someProp": int};

    let navigator = RootStack.navigator;
  });

[@react.component]
let app = () => {
  let screenProps = {"someProp": 42};
  <AppContainer screenProps />;
};