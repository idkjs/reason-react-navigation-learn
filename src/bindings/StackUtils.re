include ReactNavigation.StackNavigator;

[@bs.obj]
external config:
  (
    ~initialRouteName: string=?,
    ~defaultNavigationOptions: Js.t('a)=?,
    // was trying to pass navigationOptions in `AppContainer` but could not get it work
    // ~navigationOptions: Js.t('a)=?,
    unit
  ) =>
  config =
  "";
