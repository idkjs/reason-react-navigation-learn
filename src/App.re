// open ReactNative;
// open ReactNavigation;

[@react.component]
let app = () => {
  // open PassingParamsDemo;
  open SettingHeaderDemo;
  let screenProps = {"someProp": 42};
  <TabNavigator screenProps />;
};