// open ReactNative;
// open ReactNavigation;

[@react.component]
let app = () => {
  open PassingParamsDemo;
  let screenProps = {"someProp": 42};
  <TabNavigator screenProps />;
};