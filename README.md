# React Navigation Docs

<https://reactnavigation.org/docs/en/hello-react-navigation.html>

## InitialRouteName on `StackNavigator`

There is no `initialRouteName` config on `StackNavigator` in reason.
The initial screen is the first item in you array, here `Home`. Flip them around to see `Details` rendered first.

## [Navigating to a New Screen](https://reactnavigation.org/docs/en/navigating.html#navigating-to-a-new-screen)

## [Navigating to a Route Multiple Times](https://reactnavigation.org/docs/en/navigating.html#navigate-to-a-route-multiple-times)

 `navigate` doesnt go anywhere because you are already on this page. `push` in js, lets you indicate that you want to go to that screen anyway. I don't know if this is possible with Reason.

```reason
module DetailsScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    <Screen name="Details Screen"><Button
        title="Go to Details Screen Again"
        // js version: `onPress={() => this.props.navigation.push('Details')}`
        onPress={_ => navigation->Navigation.navigate("Details")}
      />
    </Screen>;
  };
};
```

## [Going Back](https://reactnavigation.org/docs/en/navigating.html#going-back)

Going back to previous screen in `js`:

```js
<Button
  title="Go back"
  onPress={() => this.props.navigation.goBack()}
/>
```

Going back to previous screen in `reason`:

```reason
<Button
  title="Go back"
  onPress={_ => navigation->Navigation.goBack}
/>
```
