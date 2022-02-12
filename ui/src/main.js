import SparkMD5 from 'spark-md5';
import Vue from 'vue';
import axios from 'axios';
import App from './App.vue';

Vue.config.productionTip = false;
Vue.prototype.$http = axios;
Object.defineProperty(Vue.prototype, 'SparkMD5', { value: SparkMD5 });

new Vue({
  render: (h) => h(App),
}).$mount('#app');
